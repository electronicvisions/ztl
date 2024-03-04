#!/usr/bin/env python
import sys, os

def options(opt):
    opt.recurse('test')

def configure(cfg):
    cfg.recurse('test')

def build(bld):
    bld.recurse('test')

    # install headers
    bld.install_files(
        dest = '${PREFIX}/include',
        files = bld.path.ant_glob('**/*.(h|hpp)', excl='test'),
        name = 'ztl_header',
        relative_trick = True
    )

    bld(
        target          = 'ZTL',
        export_includes = '.',
        use             = ['0TL', 'ztl_header'],
    )
