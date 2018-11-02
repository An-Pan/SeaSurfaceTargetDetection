#include <iostream>
#include <string>
#include <fstream>

#include <opencv2/opencv.hpp>

#include <boost/regex.h>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/filesystem.hpp>

#include "utils.h"

using namespace std;
using namespace cv;


void label_verify(const string& image_name, const string& label_name, const string& save_dir);

int main(int argc,char** argv) {

    label_verify("/media/ibd02/KINGSTON/000001.jpg","/media/ibd02/KINGSTON/000001.txt","/media/ibd02/KINGSTON/verify");



    return 0;
}



void label_verify(const string& image_name, const string& label_name, const string& save_dir)
{
    cv::Mat img = cv::imread(image_name);
    ifstream in_file(label_name.c_str());

    if(img.empty() || !in_file.is_open()){
        std::cout << "file empty, return." << std::endl;
        return;
    }
    char buf[1024]={0};
    while(in_file.getline(buf,1024)){
        string str = buf;
        std::vector<string> vec_items;
        boost::split(vec_items,str,boost::is_any_of(" \t"));

        if(vec_items.size() != 5){
            continue;
        }

        float x_center = boost::lexical_cast<float>(vec_items[1]);
        float y_center = boost::lexical_cast<float>(vec_items[2]);

        float width = boost::lexical_cast<float>(vec_items[3]);
        float height = boost::lexical_cast<float>(vec_items[4]);

        x_center*=img.cols;
        y_center*=img.rows;

        width*=img.cols;
        height*=img.rows;

        cv::rectangle(img,cv::Point(x_center - width/2, y_center -height/2),cv::Point(x_center + width/2, y_center + height/2),cv::Scalar(0,255,0),2);
        cv::putText(img,vec_items[0],cv::Point(x_center - width/2, y_center -height/2 - 12),cv::FONT_HERSHEY_DUPLEX,1,cv::Scalar(255,255,0),2);
        memset(buf, 0, 1024);
    }

    if(!save_dir.empty()){
        boost::filesystem::path ph(image_name);
        string name = ph.stem().string();
        cv::imwrite(save_dir+"/"+name+".jpg",img);

    }



}
