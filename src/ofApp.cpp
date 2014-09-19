#include "ofApp.h"

//----------------------------------Sets image size ----------------------------
void ofApp::setup()
{
    camWidth = 320;	// try to grab at this size.
    camHeight = 240;
    videoWidth = 900; //dms 950 worked on my computer but was too large for the MDM. Original was 800.
    videoHeight = (int)videoWidth*((float)camHeight/camWidth);
    frameRate = 5;
    arraySize=20;//dms added for more images and make it a variable
    //we can now get back a list of devices.
    vector<ofVideoDevice> devices = vidGrabber.listDevices();

    for(int i = 0; i < devices.size(); i++)
    {
        cout << devices[i].id << ": " << devices[i].deviceName;

        if( devices[i].bAvailable )
        {
            cout << endl;
        }
        else
        {
            cout << " - unavailable " << endl;
        }
    }

    //vidGrabber.setDeviceID(0); //dms uncomment if you need to pick the camera.
    vidGrabber.setDesiredFrameRate(frameRate);
    vidGrabber.initGrabber(camWidth,camHeight);

    videoArray.reserve(arraySize);
    videoCurrentBuffer = new unsigned char[camWidth*camHeight*4];
    videoOverlayBuffer = new unsigned char[camWidth*camHeight*4];
    videoCurrent = new ofTexture();
    videoCurrent->allocate(camWidth,camHeight, GL_RGBA);
    videoOverlay = new ofTexture();
    videoOverlay->allocate(camWidth,camHeight, GL_RGBA);
    ofSetVerticalSync(true);
    ofSetFullscreen(true);
    ofSetFrameRate(frameRate);

    //ofEnableAlphaBlending();
}

//--------------------------------Gets the image from the camera (I think)------------------------------
void ofApp::update()
{

    ofBackground(255,255,255);

    vidGrabber.update();
}

//------------------------------------Draws the icons and other videos--------------------------
void ofApp::draw()
{

    ofSetHexColor(0xffffff);

    int newWidth = ofGetWidth()/arraySize;
    int newHeight = (int)(ofGetWidth()/arraySize)*((float)camHeight/camWidth);
    //Print Images
    for(int i = 0; i < 20; i++)
    {


        if(i >= videoArray.size())
        {

            break;
        }
        videoArray[i].draw(i*ofGetWidth()/arraySize,ofGetHeight()-(newHeight+20),newWidth,newHeight);
    }

    if(playback && videoArray.size()>0)
    {

        videoArray[playFrame].draw((ofGetWidth()-videoWidth)/2,20,videoWidth,videoHeight);

        //put frame around array image during playback
        ofSetHexColor(0xff0000);

        ofNoFill();
        ofSetLineWidth(4.0);
        ofRect(playFrame*ofGetWidth()/20,ofGetHeight()-(newHeight+20),newWidth,newHeight);
        ofFill();


        //Increments the frame
        (++playFrame %= videoArray.size()) ;



    }
    else
    {
        vidGrabber.draw((ofGetWidth()-videoWidth)/2,arraySize,videoWidth,videoHeight);
        if(videoArray.size()>0)
            videoOverlay->draw((ofGetWidth()-videoWidth)/2,20,videoWidth,videoHeight);
    }

}
//-----------------------------------------------keyPressed p or x to save---------------
void ofApp::keyPressed(int key)
{
    // key 'p' or key 'x' is used to save the images and create a movie.

    //TODO: move this to be done by the mouse.  Maybe the mouse wheel or the move from the optical sensor.

    if (key == 'p' || key == 'x')
    {
        //makes a folder and video name using time date tags when saving and exporting.


        int day = ofGetDay();
        int hour = ofGetHours();
        int minute = ofGetMinutes();
        char timeStamp[24];
        sprintf(timeStamp,"%02d%02d%02d",day,hour,minute);
        char exportFile[100];
        ofImage img2Export;


        ofPixels pix2Export;
        for(int i = 0; i < videoArray.size(); i ++)
        {
            videoArray[i].readToPixels(pix2Export);
            img2Export.setFromPixels(pix2Export);





            sprintf(exportFile,"image-%03d.png",i);//saves the images.//dms
            img2Export.saveImage(exportFile);

        }

        char videoExportCmd[256];
        sprintf(videoExportCmd, "/usr/local/bin/ffmpeg -r %d -y -i ./data/image-%%03d.png -c:v mpeg4 -r %d -pix_fmt yuv420p ~/Desktop/data/v%s.mp4",frameRate,frameRate,timeStamp);



        system(videoExportCmd);//saves the images as a video. dms
        char deleteOldImages[24];
        sprintf(deleteOldImages, "rm data/*.png");//dms delete old images
        system(deleteOldImages);


                char exportAWS[100];
                char nameAWS[100];
                sprintf(nameAWS,"v%s.mp4",timeStamp);
                sprintf(exportAWS,"aws s3 cp ~/Desktop/data/%s s3://stopmotion/%s",nameAWS,nameAWS);
               system(exportAWS);

    }
}

//-------------mousePressed Left capture, Center playback Right delete-------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{

    //Right mouse button

    if (button == 2 )
    {
        if (videoArray.size() >= 1)
        {
            if (!playback)//dms had an error if all images were deleted during playback.
            {
                videoArray.erase(videoArray.end());
                //videoArray.size() = videoArray.size()-1;

            }
        }
    }
//--------------------------------------------------------------

    //Left mouse button
    else if (button == 0)
    {

        if (!playback)
        {
            if(videoArray.size() >= arraySize)
            {

                videoArray.erase(videoArray.begin());
            }


            int totalPixels = camWidth*camHeight*4;
            delete[] videoCurrentBuffer;
            delete[] videoOverlayBuffer;
            videoCurrentBuffer = new unsigned char[totalPixels];
            videoOverlayBuffer = new unsigned char[totalPixels];

            unsigned char * pixels = vidGrabber.getPixels();
            for (int i = 0; i < totalPixels; i++)
            {
                if(i%4 == 3)
                {
                    videoOverlayBuffer[i] = 0x80;
                    videoCurrentBuffer[i] = 0xFF;
                }
                else
                {
                    videoCurrentBuffer[i] = pixels[i-(i/4)];
                    videoOverlayBuffer[i] = pixels[i-(i/4)];
                }
            }

            delete videoOverlay;
            videoOverlay = new ofTexture();
            videoOverlay->allocate(camWidth,camHeight, GL_RGBA);
            videoOverlay->loadData(videoOverlayBuffer, camWidth, camHeight, GL_RGBA);

            delete videoCurrent;
            videoCurrent = new ofTexture();
            videoCurrent->allocate(camWidth,camHeight, GL_RGBA);
            videoCurrent->loadData(videoCurrentBuffer, camWidth, camHeight, GL_RGBA);

            videoArray.push_back(*videoCurrent);
        }
    }

    //Right mouse button
    else if (button == 1)
    {
        playback = !playback;

        playFrame = 0;

        if(videoArray.size()>0)
        {
            ofImage img2Export;
            ofPixels pix2Export;
            for(int i = 0; i < videoArray.size(); i ++)
            {
                videoArray[i].readToPixels(pix2Export);
                img2Export.setFromPixels(pix2Export);

            }
        }
    }
}


