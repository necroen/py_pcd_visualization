# 这是pybind11的源码目录中的CMakeLists.txt，下面几句是需要添加的内容，

# https://github.com/tdegeus/pybind11_examples

# 这几句放在project后，放在靠前的位置就可以了。我用的是anaconda3 python 3.6
set(PYTHON_EXECUTABLE "/home/scj/anaconda3/pkgs/python-3.6.5-hc3d631a_2/bin/python")
set(PYTHON_INCLUDE_DIRS "/home/scj/anaconda3/include/python3.6m")
set(PYTHON_LIBRARIES "/home/scj/anaconda3/lib/libpython3.6m.so")

