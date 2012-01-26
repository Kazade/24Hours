#!/usr/bin/env python

top = '.'
out = 'build'
 
def options(opt):
    opt.load('compiler_c compiler_cxx')
 
def configure(conf):
    conf.load('compiler_c compiler_cxx boost')
    conf.check_tool('boost')
    conf.check_boost('system filesystem thread date_time regex')
    conf.check_cfg(package="libcurl", args="--libs --cflags", uselib_store="CURL")    
    conf.check_cfg(package="unittest++", args="--libs --cflags", uselib_store="UNITTEST")

    conf.env.CXXFLAGS = ['-g', '-w', '-std=c++0x']
 
def build(bld):
    bld.read_shlib('SOIL', paths=['.', '/usr/lib'])

    tests = bld.new_task_gen(
        features = "cxx cxxprogram",
        target = "unit_tests",
        uselib = "UNITTEST CURL",
        use = [ "BOOST",  "SOIL" ]
    )
    
    tests.includes = "src /usr/include/SOIL"
    tests.source = tests.path.make_node("tests").ant_glob("**/*cpp")
    tests.source += tests.path.make_node("src").ant_glob("**/*cpp", excl=["kazbase/gtk/flattr_button.cpp", "kazbase/gtk/switch_menu.cpp", "kazbase/tests.cpp"])

    tests.install_path = None

    import shutil, os
    dest = os.path.join(out, "test-data")
    if os.path.exists(dest):
        shutil.rmtree(dest)
        
    shutil.copytree("tests/test-data", dest)

