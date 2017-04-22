//
// Created by 逸帆 杨 on 2017/4/16.
//
#include<jni.h>
#include<vector>

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/stitching/stitcher.hpp"


using namespace cv;
using namespace std;
char filepath1[100]="/Users/yifanyang/Desktop/NDK/panorama_stitched.jpg";
//声明函数
extern "C" {
    JNIEXPORT jint JNICALL Java_com_example_yifanyang_imagemosaicking_StitchingActivity_StitchPanorama(JNIEnv*, jobject, jobjectArray, jint, jlong);
    JNIEXPORT jint JNICALL Java_com_example_yifanyang_imagemosaicking_StitchingActivity_StitchPanorama(JNIEnv* env, jobject, jobjectArray images, jint size, jlong resultMatAddr)
    {
        jint result = 0;
        vector<Mat> clickedImages = vector<Mat>();
        Mat& srcRes = *(Mat*)resultMatAddr, img;
        Mat output_stitched = Mat();

        jclass clazz = (env)->FindClass("org/opencv/core/Mat");
        jmethodID getNativeObjAddr = (env)->GetMethodID(clazz, "getNativeObjAddr", "()J");

        for(int i=0; i < size; i++){
            jobject obj = (env->GetObjectArrayElement(images, i));
            jlong result = (env)->CallLongMethod(obj, getNativeObjAddr, NULL);
            img = *(Mat*)result;
            resize(img, img, Size(img.rows/10, img.cols/10));
            clickedImages.push_back(img);
            env->DeleteLocalRef(obj);
        }
        env->DeleteLocalRef(images);

        Stitcher stitcher = Stitcher::createDefault();
        Stitcher::Status status = stitcher.stitch(clickedImages, output_stitched);

        output_stitched.copyTo(srcRes);

        imwrite(filepath1, srcRes);

        if (status == Stitcher::OK)
            result = 1;
        else
            result = 0;

        return result;
    }
}
