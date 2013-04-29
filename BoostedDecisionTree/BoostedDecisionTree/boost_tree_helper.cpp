//
//  boost_tree_helper.cpp
//  BoostedDecisionTree
//
//  Created by Ze Wang on 4/27/13.
//  Copyright (c) 2013 Ze Wang. All rights reserved.
//

#include "boost_tree_helper.h"
#include <string>
#include <fstream>
#include <iterator>
#include <iostream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include "data_processor.h"
#include "math_util.h"
#include "stump_classifier.h"
#include "boost_classifier.h"



void train(po::variables_map vm) throw (std::exception)
{
    std::ofstream ofs;
    try{
        ofs.open(vm["final_predictor"].as<std::string>().c_str());
        std::pair<matrix_ptr_type,long_vector_ptr_type> data_pair = data_processor::load_data(std::cin);
        boost_classifier bc;
        bc.preprocess(data_pair.first, data_pair.second,EPS);
        
        vector_ptr_type weights(new uvector(0));//stub weights for boost classifier
        bc.learn(weights);
        {
            boost::archive::text_oarchive oa(ofs);
            oa<<bc;
        }
    }catch(std::exception& e){
        throw e;
    }
    
}

void print_verbose_report(long_vector_ptr_type predicted_labels,long_vector_ptr_type original_labels){
    long tp = 0;
    long fp = 0;
    long fn = 0;
    float precision,recall,error;
    
    for(long i = 0;i<predicted_labels->size();i++){
        if((*predicted_labels)(i) * (*original_labels)(i) > 0){// correct prediction
            if((*predicted_labels)(i)>0){
                tp++;
            }
        }else{// error prediction
            if((*predicted_labels)(i)>0){
                fp++;
            }else{
                fn++;
            }
        }
    }
    long all_predicted_p = tp+fp;
    long all_p = tp+fn;
 
    precision = all_p!=0?tp/all_p:0;
    recall = all_predicted_p!=0?tp/all_predicted_p:0;
    error = (fp+fn)/predicted_labels->size();
    std::cout<<"Precision is "<<precision<<std::endl;
    std::cout<<"Recall is "<<recall<<std::endl;
    std::cout<<"error rate  is "<<error<<std::endl;
}

void predict(po::variables_map vm) throw (std::exception)
{
    if(!vm.count("output")){
        std::cerr<<"please specified the output path for prediction results"<<std::endl;
        throw std::exception();
    }
    
    std::ifstream predictor_ifs;
    std::ofstream result_ofs;
    
    try{
        predictor_ifs.open(vm["predictor"].as<std::string>().c_str());
        result_ofs.open(vm["output"].as<std::string>().c_str());
        std::pair<matrix_ptr_type,long_vector_ptr_type> data_pair = data_processor::load_data(std::cin);
        boost_classifier bc;
        {
            boost::archive::text_iarchive ia(predictor_ifs);
            ia>>bc;
        }
        long_vector_ptr_type predicted_labels = bc.predict(data_pair.first);
        std::copy(predicted_labels->begin(), predicted_labels->end(), std::ostream_iterator<float>(result_ofs,"\n"));
        
        if(vm.count("verbose")){//print verbose report
            print_verbose_report(predicted_labels,data_pair.second);
        }
    }catch(std::exception& e){
        throw e;
    }
}