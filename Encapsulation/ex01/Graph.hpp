#ifndef GRAPH_H
#define GRAPH_H

#include <utility>
#include <vector>
#include <algorithm>
#include <iostream> 
#include <iomanip>
#include <cmath>
#include <fstream>
#include <string>
#include <sstream>


class Graph {



    private:
        int size;
        std::vector<std::pair<float,float> > Vector2;

    public:
        Graph(): size(0){}
        ~Graph(){}
        //add a method to add a point to the graph
        void addPoint(float x, float y){
            //check for negative numbers
            if (x < 0 || y < 0)
                throw std::invalid_argument("Failed to add point: Invalid coordinates");
            Vector2.push_back(std::make_pair(x,y));
            size++;
        }
        //add a method to output the graph in the terminal

        bool checkforPoint(float x, float y, float x_step, float y_step){
            for (int i=0; i < (int)Vector2.size(); i++){
                //check if there is a close point
                //first check if the x is close
                float x_tmp1 = fabs(Vector2[i].first - x);
                if (x_tmp1 < x_step)
                {
                    //check x for next  and previous points and campare the result
                    float x_tmp2 = fabs((x + x_step) - Vector2[i].first);
                    float x_tmp3 = fabs((x - x_step) - Vector2[i].first);
                    if (x_tmp2 < x_tmp1 || x_tmp3 < x_tmp1)
                        continue;
                    //check if the y is close
                    float y_tmp1 = fabs(Vector2[i].second - y);
                    if (y_tmp1 < y_step){
                        float y_tmp2 = fabs((y - y_step) - Vector2[i].second);
                        float y_tmp3 = fabs((y + y_step) - Vector2[i].second);
                        if (y_tmp3 < y_tmp1 || y_tmp2 <  y_tmp1)
                            continue;
                    //debug
                    // std::cerr<<"close point-----------------------------------"<<std::endl;
                    // std::cerr<<"delta_x = "<<x_tmp1<< "delta_y = "<<y_tmp1<<std::endl;
                    // std::cerr<<"x: "<<Vector2[i].first<<"y: "<<Vector2[i].second<<std::endl;
                    // std::cerr<<"x_axis: "<<x<<"y_axis: "<<y<<std::endl;
                    //end debug
                        return true;
                    }
                }
            }
            return false;
        }

        void printGraph(){
            //get the max value of x and y
            
            float max_x = 0;
            float max_y = 0;
            std::vector<float> x_axis;
            std::vector<float> y_axis;
            for (int i=0; i < (int)Vector2.size(); i++){
                if (Vector2[i].first > max_x)
                    max_x = Vector2[i].first;
                if (Vector2[i].second > max_y)
                    max_y = Vector2[i].second;
                x_axis.push_back(Vector2[i].first);
                y_axis.push_back(Vector2[i].second);
            }
            //calculate the x step and  y step
            max_x += 1;
            max_y += 1;
            float x_step = 1;
            float y_step = 1;
            std::sort(x_axis.begin(), x_axis.end());
            std::sort(y_axis.begin(), y_axis.end());
            for (int i = 0; i < (int)x_axis.size() - 1; i++){
                float x_tmp = x_axis[i+1] - x_axis[i];
                if (x_tmp < x_step && x_tmp != 0)
                    x_step = x_tmp;
                float y_tmp = y_axis[i+1] - y_axis[i];
                if (y_tmp < y_step && y_tmp != 0 )
                    y_step = y_tmp;
            }
            //draw the graph
            while(max_y > 0){
                //draw y axis
                std::cout<<std::setw(4)<<max_y;
                //draw points 
                float tmp = 0;
                while(tmp <= max_x){
                    //check if there is a point
                    if (checkforPoint(tmp, max_y, x_step, y_step))
                        std::cout<<std::setw(4)<<"X";
                    else
                        std::cout<<std::setw(4)<<".";
                    tmp += x_step;
                }
                std::cout<<std::endl;
                max_y -= y_step;
            }
            //last line of points
            //draw y axis
            std::cout<<std::setw(4)<<'0';
            //draw points 
            float tmp = 0;
            while(tmp <= max_x){
                //check if there is a point
                if (checkforPoint(tmp, max_y, x_step, y_step))
                    std::cout<<std::setw(4)<<"X";
                else
                    std::cout<<std::setw(4)<<".";
                tmp += x_step;
            }
            std::cout<<std::endl;

            //draw the x axis
            std::cout<<std::setw(4)<<" ";
            float i=0;
            while(i<=max_x){
                std::cout<<std::setw(4)<<i;
                i += x_step;
            }

        }


        //add method to read input file
        void readInputFile(std::string filename){
            //read file line by line
            //add point to the graph
            std::fstream file(filename);
            std::string buff;

            if (!file.is_open())
                throw std::invalid_argument("Failed to read input file: Invalid file");

            while(getline(file, buff)){
                //pase the line and get the x and y
                std::istringstream ss(buff);
                std::string xAsString;
                std::string yAsString;
                std::string sep;

                ss>>xAsString>>sep>>yAsString;
                //convert the strings to floats + check if the sep is a comma
                float x = std::stof(xAsString);
                float y = std::stof(yAsString);
                //debug
                std::cerr<<"x: "<<x<<" y: "<<y<<std::endl;
                //end debug
                if(sep.compare(","))
                    throw std::invalid_argument("Failed to read input file: Invalid separator");
                else if (x < 0 || y < 0 )
                    throw std::invalid_argument("Failed to read input file: Invalid coordinates");
                addPoint(x, y);
            }
            file.close();
        }
};
#endif

