#!/usr/bin/env python
import sys, os

def options(opt):
    opt.recurse('test')

def configure(cfg):
    cfg.recurse('test')

def build(bld):
    bld.recurse('test')

    bld(
        target          = 'ZTL',
        export_includes = '.',
        use             = '0TL',
    )
