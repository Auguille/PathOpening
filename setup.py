from setuptools import setup

setup(
   name='PathOpening',
   description='A useful module for path opening and closing',
   author='Hiernard Craig',
   author_email='craig.hiernard@gmail.com',
   packages=[''],  #same as name
   package_dir={'': 'build'},
   package_data={'': ['PathOpening.so']},
)