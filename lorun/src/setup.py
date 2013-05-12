#!/usr/bin/python
#-*coding:utf-8*-

from distutils.core import setup, Extension

baserun = Extension('lorun',
                sources = ['lorun.c','convert.c','access.c','limit.c','run.c','diff.c'],
                )

setup (name = 'lorun',
       version = '1.0',
       description = 'loco program runner core',
       ext_modules = [baserun]
      )
