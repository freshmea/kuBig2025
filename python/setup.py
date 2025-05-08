from setuptools import Extension, setup

module = Extension("mymodule", sources=['mymodule.c'])
setup(name = 'mymodule', version='1.0', ext_modules=[module])

# poetry
# uv
