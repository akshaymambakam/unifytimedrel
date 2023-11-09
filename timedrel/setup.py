import setuptools

from distutils import util
from distutils.core import setup
from distutils.extension import Extension

ext_instance_int = Extension(
    'ext_int',
    sources=['timedrel/boost/timedrel_ext_int.cpp'],
    include_dirs=['include'],
    libraries=['boost_python3'],
)

ext_instance_float = Extension(
    'ext_float',
    sources=['timedrel/boost/timedrel_ext_float.cpp'],
    include_dirs=['include'],
    libraries=['boost_python3'],
)

setup(
    name='timedrel',

    version='0.3.0',
    author='Dogan Ulus',
    author_email='doganulus@gmail.com',
    url='http://github.com/doganulus/timedrel/',
    packages=setuptools.find_packages(),
    license='GPLv3+',
    description = 'timedrel implements timed relations',
    python_requires='>=3',

    ext_package='timedrel',
    ext_modules=[ext_instance_int, ext_instance_float]

)