# -*- coding: utf-8 -*-

from tymer import t, skip


setup_tymer = """
import tldextract, posixpath, urlparse

from urltools.urltools import construct, parse, extract, encode, split, split_netloc
from urltools.urltools import normalize, normalize_path, normalize_query, unquote
from urltools.urltools import _get_public_suffix_list, _clean_netloc
"""


@skip
def tymer__get_public_suffix_list():
    t('_get_public_suffix_list()')


@skip
def tymer_normalize():
    t('normalize("http://WwW.exAmple.com./a/b/..////c?x=1#abc")')


@skip
def tymer_normalize_path():
    t('normalize_path("/foo////../bar/./a/b/")')
    t('posixpath.normpath("/foo////../bar/./a/b/")')


@skip
def tymer_normalize_query():
    t('normalize_query("")')
    t('normalize_query("x=1")')
    t('normalize_query("x=1&y=&z=3")')


@skip
def tymer_unquote():
    t('unquote("%25%32%35")')
    t('urlparse.unquote("%25%32%35")')


@skip
def tymer_parse():
    t('parse("http://example.com")')
    t('extract("http://example.com")')
    t('urlparse.urlparse("http://example.com")')
    t('tldextract.extract("http://example.com")')


@skip
def tymer_split():
    t('urlparse.urlparse("http://example.com")')
    t('split("http://example.com")')


@skip
def tymer_split_netloc():
    t('split_netloc("foo:bar@www.example.com:8080")')


@skip
def tymer__clean_netloc():
    t('_clean_netloc("ПриМЕр.Рф")')
    t('_clean_netloc("example.com:")')
    t('_clean_netloc("fOO.baR.example.com")')


@skip
def tymer_construct():
    t("""
    parts = extract("http://www.example.com:8080/abc?x=1#rt")
    construct(parts)
    """)
