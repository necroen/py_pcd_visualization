// 从python接收点云数据并显示

#include <iostream>

#include <pcl/io/pcd_io.h>                      
#include <pcl/point_types.h>                   
#include <pcl/visualization/cloud_viewer.h>   


#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>

namespace py = pybind11;

int showpcd(py::array_t<double>& input1) 
{
    py::buffer_info buf1 = input1.request();

    double* ptr1 = (double*)buf1.ptr;  //指针访问读写 numpy.ndarray

    if (buf1.ndim != 2)
    {
        throw std::runtime_error("numpy.ndarray dims must be 2!");
    }

    auto h = buf1.shape[0];
    auto w = buf1.shape[1];

    std::cout << "===================="<< std::endl;

    // 定义点云使用的格式：这里用的是XYZRGB
    typedef pcl::PointXYZRGB PointT; 
    typedef pcl::PointCloud<PointT> PointCloud;
    
    // 新建一个点云
    PointCloud::Ptr pointCloud( new PointCloud ); 


    for (int i = 0; i < buf1.shape[0]; i++)
    {
        // for (int j = 0; j < buf1.shape[1]; j++)
        // {
        //     auto value = ptr1[i*buf1.shape[1] + j];
        //     std::cout << "value:" << value << std::endl;
        // }

        PointT p ;
        p.x = ptr1[i*buf1.shape[1] + 0];
        p.y = ptr1[i*buf1.shape[1] + 1];
        p.z = ptr1[i*buf1.shape[1] + 2];

        p.b = ptr1[i*buf1.shape[1] + 3];
        p.g = ptr1[i*buf1.shape[1] + 4];
        p.r = ptr1[i*buf1.shape[1] + 5];
        
        pointCloud->points.push_back( p );

    }

    pointCloud->is_dense = false;
    cout<<"number of points:"<< pointCloud->size() <<endl;
    // pcl::io::savePCDFileBinary("map.pcd", *pointCloud );


    //直接创造一个显示窗口
    pcl::visualization::CloudViewer viewer("Simple Cloud Viewer");
    viewer.showCloud(pointCloud); //在这个窗口显示点云

    while (!viewer.wasStopped())
    {
    }

    return 1;

}

PYBIND11_MODULE(example, m) {

    m.doc() = "get pcd from python!";
    m.def("showpcd", &showpcd);

}