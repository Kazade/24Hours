#!/usr/bin/env python

top = '.'
out = 'build'
 
def options(opt):
    opt.load('compiler_c compiler_cxx boost')
 
def configure(conf):
    conf.load('compiler_c compiler_cxx boost')
    conf.check_tool('boost')
    conf.check_boost('system filesystem thread date_time regex')
    conf.check_cfg(package="unittest++", args="--libs --cflags", uselib_store="UNITTEST")
    conf.env.CXXFLAGS = ['-g', '-w', '-std=c++0x']
 
def build(bld):
    tests = bld.new_task_gen(
        features = "cxx cxxprogram",
        target = "unit_tests",
        uselib = "UNITTEST",
        use = [ "BOOST" ]
    )
    
    tests.includes = "src"
    tests.source = tests.path.make_node("tests").ant_glob("**/*cpp")
    tests.source += tests.path.make_node("src").ant_glob("**/*cpp")
    tests.install_path = None

