#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup()
{
    camWidth = 320;	// try to grab at this size.
    camHeight = 240;
    videoWidth = 950;
    videoHeight = (int)videoWidth*((float)camHeight/camWidth);
    frameRate = 5;
    arraySize=20;//dms added per request from tp for more images.
    //we can now get back a list of devices.
    vector<ofVideoDevice> devices = vidGrabber.listDevices();

    for(int i = 0; i < devices.size(); i++)
    {        cout << devices[i].id << ": " << devices[i].deviceName;

        if( devices[i].bAvailable )
        {            cout << endl;
        }
        else
        {            cout << " - unavailable " << endl;
        }
    }

//vidGrabber.setDeviceID(0);
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

//--------------------------------------------------------------
void ofApp::update()
{

    ofBackground(255,255,255);

    vidGrabber.update();
}

//--------------------------------------------------------------
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
        //Draw big picture
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

void ofApp::keyPressed(int key)
{    // key 'p' or key 'x' is used to save the images and create a movie.

    //TODO move this to be done by the mouse.  Maybe the mouse wheel or the move from the optical sensor.

    if (key == 'p' || key == 'x')
    {//makes a folder and video name using time date tags when saving and exporting.
        int year = ofGetYear();
        int month= ofGetMonth();
        int day = ofGetDay();
        int hour = ofGetHours();
        int minute = ofGetMinutes();
        char timeStamp[24];
        sprintf(timeStamp,"%04d%02d%02d%02d%02d",year,month,day,hour,minute);

        ofImage img2Export;
        ofPixels pix2Export;
        for(int i = 0; i < videoArray.size(); i ++)
        {
            videoArray[i].readToPixels(pix2Export);
            img2Export.setFromPixels(pix2Export);
            char exportFile[100];



            sprintf(exportFile,"%s/image-%03d.png",timeStamp,i);//creates a folder and saves the images.

            img2Export.saveImage(exportFile);

        }

        char videoExportCmd[256];

        sprintf(videoExportCmd, "/usr/local/bin/ffmpeg -r %d -y -i data/%s/image-%%03d.png -c:v mpeg4 -r %d -pix_fmt yuv420p data/v%s.mp4",frameRate,timeStamp,frameRate,timeStamp);
        //sprintf(videoExportCmd, "/usr/local/bin/ffmpeg -r %d -y -i data/20149101230/image-%%03d.png -c:v mpeg4 -r %d -pix_fmt yuv420p v%d%d%d%d%d.mp4",year,month,day,hour,minute,frameRate,frameRate,year,month,day,hour,minute);

        system(videoExportCmd);//saves the images as a video.

        //system("mkdir %d%d%d%d%d",year,month,day,hour,minute);//make timestamp dir for archive;
        //system("cp *.png %d%d%d%d%d",year,month,day,hour,minute);
        //system("rm *.png");//TODO move to timestamp);
//system(aws configure);//if needed
//aws s3 ls s3://stopmotion
        char exportAWS[100];
        char nameAWS[100];
        sprintf(nameAWS,"v%s.mp4",timeStamp);
       sprintf(exportAWS,"aws s3 cp data/%s s3://stopmotion/%s",nameAWS,nameAWS);
       system(exportAWS);

    }
}


//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//-----------------------------------------------keyPressed---------------
void ofApp::mouseMoved(int x, int y ){
int keyPressed(1);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{//TODO make the overlay image the previous image.

//Right mouse key is used to delete the last image along the bottom of the screen.
//TODO make the overlay image the previous image.
    if (button == 2 )
    {        if (videoArray.size() >= 1)
        {            videoArray.erase(videoArray.end());
            //videoArray.size() = videoArray.size()-1;
        }

    }
    //Left mouse key is used to add another image to the array.
    else if (button == 0)
    {       //If the array has 10 images the first one will be deleted when an image is added.
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

        //center key is used for playback the images which are stored along the bottom of the screen.
    }
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
                /*                char exportFile[100];

                sprintf(exportFile,"/home/denis/Desktop/stopMotion/export/images/image-%03d.png",i);

                img2Export.saveImage(exportFile);

            }

            char videoExportCmd[256];
            int timestamp = ofGetUnixTime();
            //TODO filename to date and time
            sprintf(videoExportCmd, "/usr/local/bin/ffmpeg -r %d -y -i ./export/images/image-%%03d.png -c:v mpeg4 -r %d -pix_fmt yuv420p /home/denis/Desktop/stopMotion/export/videos/v%d.mp4",frameRate,frameRate,timestamp);

            system(videoExportCmd);//saves the images as a video.

            system("mv   ./export/images/*.png test");//TODO edit this to timestamp);

             system("aws  s3 cp //home/denis/Desktop/stopMotion/export/videos/v1410101781.mp4  s3 //stopmotion/file.jpg");
             }
    }
*/

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
}
//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
}
