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
    conf.check_cfg(package="gl", args="--libs --cflags", uselib_store="GL")
    conf.check_cfg(package="glu", args="--libs --cflags", uselib_store="GLU")    
    conf.check_cfg(package="sdl", args="--libs --cflags", uselib_store="SDL")
    conf.check_cfg(package="sigc++-2.0", args="--libs --cflags", uselib_store="SIGC")
    conf.env.CXXFLAGS = ['-g', '-w', '-std=c++0x']
 
def build(bld):
    bld.read_shlib('SOIL', paths=['.', '/usr/lib'])

    tests = bld.new_task_gen(
        features = "cxx cxxprogram",
        target = "unit_tests",
        uselib = "UNITTEST CURL GL GLU SDL SIGC",
        use = [ "BOOST",  "SOIL" ]
    )
    
    tests.includes = "src kglt/src /usr/include/SOIL"
    tests.source = tests.path.make_node("tests").ant_glob("**/*cpp")
    tests.source += tests.path.make_node("kglt/src").ant_glob("**/*c")
    tests.source += tests.path.make_node("kglt/src").ant_glob("**/*cpp", excl=[
        "kazbase/gtk/flattr_button.cpp", 
        "kazbase/gtk/switch_menu.cpp", 
        "kazbase/tests.cpp",
        "sample.cpp",
        "q2bsp_sample.cpp"
    ])
    tests.source += tests.path.make_node("src").ant_glob("**/*cpp")
    tests.install_path = None

    import shutil, os
    dest = os.path.join(out, "test-data")
    if os.path.exists(dest):
        shutil.rmtree(dest)
        
    shutil.copytree("tests/test-data", dest)

