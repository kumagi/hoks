def options(opt):
  opt.load('compiler_cxx')
  opt.load('unittest_gtest')
  opt.load('gnu_dirs')

def configure(conf):
  conf.env.CXXFLAGS += ['-O2', '-Wall', '-g', '-pipe']

  conf.load('compiler_cxx')
  conf.load('unittest_gtest')
  conf.load('gnu_dirs')

def build(bld):
  bld.program(
    features='gtest',
    source='hoks_test.cpp hoks.cpp MurmurHash3.cpp',
    target='hoks',
    includes='.',
    use=''
    )
