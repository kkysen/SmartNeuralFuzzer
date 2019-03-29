# -*- coding: utf-8 -*-
import pytest

from urltools import parse, extract, encode, split, split_netloc, split_host
from urltools import normalize, normalize_path, normalize_query, unquote
from urltools import normalize_host, normalize_fragment, compare
from urltools.urltools import _get_public_suffix_list, _clean_netloc
from urltools.urltools import _normalize_port, _encode_query


def test_get_public_suffix_list():
    psl = _get_public_suffix_list()
    assert 'de' in psl
    assert len(psl) > 6000
    assert '' not in psl


def test_normalize():
    assert normalize('') == ''
    assert normalize('http://example.com') == 'http://example.com/'
    assert normalize('http://example.com/') == 'http://example.com/'
    assert normalize('    http://example.com/      ') == 'http://example.com/'
    assert normalize('https://example.com/') == 'https://example.com/'
    assert normalize('hTTp://example.com/') == 'http://example.com/'
    assert normalize('http://ExAMPLe.COM/') == 'http://example.com/'
    assert normalize('http://example.com./') == 'http://example.com/'
    assert normalize('http://example.com:/') == 'http://example.com/'
    assert normalize('http://example.com/#') == 'http://example.com/'

    # subdomain
    assert normalize('http://www.example.com/') == 'http://www.example.com/'
    assert normalize('http://www.example.com') == 'http://www.example.com/'
    assert normalize('http://foo.bar.example.com/') == 'http://foo.bar.example.com/'

    # port
    assert normalize('http://example.com:80/') == 'http://example.com/'
    assert normalize('https://example.com:443/') == 'https://example.com/'
    assert normalize('ws://example.com:80/') == 'ws://example.com/'
    assert normalize('http://example.com:8080/') == 'http://example.com:8080/'

    # path
    assert normalize('http://example.com/a') == 'http://example.com/a'
    assert normalize('http://example.com/a/b/c') == 'http://example.com/a/b/c'
    assert normalize('http://example.com/foo/') == 'http://example.com/foo/'
    assert normalize('http://example.com/a/./b/././c') == 'http://example.com/a/b/c'
    assert normalize('http://example.com/a/../b') == 'http://example.com/b'
    assert normalize('http://example.com/./b') == 'http://example.com/b'
    assert normalize('http://example.com/../b') == 'http://example.com/b'
    assert normalize('http://example.com/////////foo') == 'http://example.com/foo'
    assert normalize('http://example.com/foo/.../bar') == 'http://example.com/foo/.../bar'
    assert normalize('http://example.com/foo+bar') == 'http://example.com/foo+bar'
    assert normalize('http://example.com/.') == 'http://example.com/'
    assert normalize('http://example.com/..') == 'http://example.com/'
    assert normalize('http://example.com/./') == 'http://example.com/'
    assert normalize('http://example.com/../') == 'http://example.com/'
    assert normalize('http://example.com/a/..') == 'http://example.com/'
    assert normalize('http://example.com/a/../') == 'http://example.com/'

    # encoded path
    assert normalize('http://example.com/%25%32%35') == 'http://example.com/%25'
    assert normalize('http://example.com/foo%25%32%35bar') == 'http://example.com/foo%25bar'
    assert normalize('http://example.com/foo/%25%32%35/bar') == 'http://example.com/foo/%25/bar'
    assert normalize('http://example.com/%7Efoo') == 'http://example.com/~foo'
    assert normalize('http://example.com/foo%23bar') == 'http://example.com/foo%23bar'  # %23 = #

    # query
    assert normalize('http://example.com/?x=1') == 'http://example.com/?x=1'
    assert normalize('http://example.com?x=1') == 'http://example.com/?x=1'
    assert normalize('http://example.com/a?x=1') == 'http://example.com/a?x=1'
    assert normalize('http://example.com/a/?x=1') == 'http://example.com/a/?x=1'
    assert normalize('http://example.com/a?x=1&y=2') == 'http://example.com/a?x=1&y=2'
    assert normalize('http://example.com/a?y=2&x=1') == 'http://example.com/a?x=1&y=2'
    assert normalize('http://example.com/a?x=&y=2') == 'http://example.com/a?y=2'

    # fragment
    assert normalize('http://example.com/#abc') == 'http://example.com/#abc'
    assert normalize('http://example.com/a/b/c#abc') == 'http://example.com/a/b/c#abc'
    assert normalize('http://example.com/a/b/c?x=1#abc') == 'http://example.com/a/b/c?x=1#abc'

    # username/password
    assert normalize('http://foo:bar@example.com') == 'http://foo:bar@example.com/'
    assert normalize('http://Foo:BAR@exaMPLE.COM/') == 'http://Foo:BAR@example.com/'

    # scheme without //
    assert normalize('mailto:foo@example.com') == 'mailto:foo@example.com'
    assert normalize('mailto:foo@eXAMPle.cOM') == 'mailto:foo@example.com'


def test_normalize__idn():
    assert normalize('http://xn--e1afmkfd.xn--p1ai/') == u'http://пример.рф/'


def test_normalize__no_scheme():
    assert normalize('eXAmplE.com') == 'example.com'
    assert normalize('example.com/a/../b') == 'example.com/b'
    assert normalize('www.example.com') == 'www.example.com'


def test_normalize__ip4():
    assert normalize('http://192.168.1.1/') == 'http://192.168.1.1/'
    assert normalize('http://192.168.1.1:8088/foo?x=1') == 'http://192.168.1.1:8088/foo?x=1'
    assert normalize('192.168.1.1') == '192.168.1.1'
    assert normalize('192.168.1.1:8080/foo/bar') == '192.168.1.1:8080/foo/bar'


def test_normalize__ip6():
    assert normalize('[::1]') == '[::1]'
    assert normalize('http://[::1]') == 'http://[::1]/'
    assert normalize('[::1]:8080') == '[::1]:8080'
    assert normalize('http://[::1]:8080') == 'http://[::1]:8080/'


def test_normalize__malformed():
    assert normalize('http://example.com/?foo') == 'http://example.com/'
    assert normalize('http://example.com?foo') == 'http://example.com/'
    assert normalize('http://example.com/foo//bar') == 'http://example.com/foo/bar'
    assert normalize('http://example.com?') == 'http://example.com/'
    assert normalize('http://example.com/?') == 'http://example.com/'
    assert normalize('http://example.com//?') == 'http://example.com/'
    assert normalize('http://example.com/foo/?http://example.com/bar/?x=http://examle.com/y/z') == 'http://example.com/foo/?http://example.com/bar/?x=http://examle.com/y/z'
    assert normalize('http://example.com/#foo?bar') == 'http://example.com/#foo?bar'
    assert normalize('http://example.com/#foo/bar/blub.html?x=1') == 'http://example.com/#foo/bar/blub.html?x=1'
    assert normalize('http://example.com/foo#?=bar') == 'http://example.com/foo#?=bar'
    assert normalize('http://example.com/foo/bar/http://example.com') == 'http://example.com/foo/bar/http:/example.com'


def test_normalize_host():
    assert normalize_host('xn--e1afmkfd.xn--p1ai') == u'пример.рф'
    assert normalize_host('xn--mller-kva.de') == u'müller.de'


def test_normalize_port():
    assert _normalize_port('http', '80') is None
    assert _normalize_port('http', '8080') == '8080'


def test_normalize_path():
    assert normalize_path('') == '/'
    assert normalize_path('/') == '/'
    assert normalize_path('/a') == '/a'
    assert normalize_path('/a/') == '/a/'
    assert normalize_path('/a/b') == '/a/b'
    assert normalize_path('/a/b/') == '/a/b/'
    assert normalize_path('/a/b/c') == '/a/b/c'
    assert normalize_path('/.') == '/'
    assert normalize_path('/./') == '/'
    assert normalize_path('/..') == '/'
    assert normalize_path('/../') == '/'
    assert normalize_path('/a/./b/././c') == '/a/b/c'
    assert normalize_path('/a/../b') == '/b'
    assert normalize_path('/a/b/../../c') == '/c'
    assert normalize_path('/////////foo') == '/foo'
    assert normalize_path('/foo/.../bar') == '/foo/.../bar'
    assert normalize_path('%25%32%35') == '%25'


def test_normalize_path__relative():
    assert normalize_path('a') == 'a'


def test_normalize_query():
    assert normalize_query('') == ''
    assert normalize_query('x=1&y=2') == 'x=1&y=2'
    assert normalize_query('y=2&x=1') == 'x=1&y=2'
    assert normalize_query('x=1&y=&z=3') == 'x=1&z=3'
    assert normalize_query('x=&y=&z=') == ''
    assert normalize_query('=1&=2&=3') == ''


def test_normalize_fragment():
    assert normalize_fragment('foo%25%32%35bar') == 'foo%25bar'
    assert normalize_fragment('foo%23bar') == 'foo%23bar'


def test_compare():
    assert compare("http://examPLe.com:80/abc?x=&b=1", "http://eXAmple.com/abc?b=1") is True
    assert compare("http://examPLe.com:80/abc?x=&b=1", "http://eXAmple.com/abc/de?b=1") is False


def test_unquote():
    pytest.raises(TypeError, unquote, None)
    assert unquote('') == ''
    assert unquote('%32%35') == '25'
    assert unquote('%25%32%35') == '%25'
    assert unquote('%25%32%35', ['%']) == '%2525'
    assert unquote('foo%25%32%35bar') == 'foo%25bar'
    assert unquote('foo%23bar') == 'foo#bar'
    assert unquote('foo%23bar', ['#']) == 'foo%23bar'
    assert unquote('%2e%2E') == '..'


def test_encode():
    assert encode(u'http://exämple.com') == 'http://xn--exmple-cua.com'
    assert encode(u'http://müller.de/') == 'http://xn--mller-kva.de/'
    assert encode(u'http://ジェーピーニック.jp/') == 'http://xn--hckqz9bzb1cyrb.jp/'
    assert encode(u'http://пример.рф') == 'http://xn--e1afmkfd.xn--p1ai'
    assert encode(u'пример.рф') == 'xn--e1afmkfd.xn--p1ai'
    assert encode(u'http://exämple.com/mühüü') == 'http://xn--exmple-cua.com/m%C3%BCh%C3%BC%C3%BC'
    assert encode(u'http://example.com/?x=mühüü') == 'http://example.com/?x=m%C3%BCh%C3%BC%C3%BC'


def test__encode_query():
    assert _encode_query('x=abc') == 'x=abc'
    assert _encode_query(u'x=mühüü') == 'x=m%C3%BCh%C3%BC%C3%BC'


def test_parse():
    assert parse('http://example.com') == ('http', '', '', '', 'example', 'com', '', '', '', '', 'http://example.com')
    assert parse('http://example.com:8080') == ('http', '', '', '', 'example', 'com', '8080', '', '', '', 'http://example.com:8080')
    assert parse('http://example.co.uk') == ('http', '', '', '', 'example', 'co.uk', '', '', '', '', 'http://example.co.uk')
    assert parse('http://example.com/foo/') == ('http', '', '', '', 'example', 'com', '', '/foo/', '', '', 'http://example.com/foo/')
    assert parse('http://foo:bar@www.example.com:1234/foo/?x=1#bla') == ('http', 'foo', 'bar', 'www', 'example', 'com', '1234', '/foo/', 'x=1', 'bla', 'http://foo:bar@www.example.com:1234/foo/?x=1#bla')
    assert parse('http://example.com?foo=bar:blub') == ('http', '', '', '', 'example', 'com', '', '', 'foo=bar:blub', '', 'http://example.com?foo=bar:blub')
    assert parse('http://example.com?foo=bar:blub/') == ('http', '', '', '', 'example', 'com', '', '', 'foo=bar:blub/', '', 'http://example.com?foo=bar:blub/')

    assert parse('mailto:foo@bar.com') == ('mailto', 'foo', '', '', 'bar', 'com', '', '', '', '', 'mailto:foo@bar.com')


def test_parse__idn():
    assert parse(u'http://пример.рф') == ('http', '', '', '', u'пример', u'рф', '', '', '', '', u'http://пример.рф')
    assert parse(u'http://إختبار.مصر/') == ('http', '', '', '', u'إختبار', u'مصر', '', '/', '', '', u'http://إختبار.مصر/')


def test_parse__no_scheme():
    assert parse('example.com.') == ('', '', '', '', '', '', '', 'example.com.', '', '', 'example.com.')
    assert parse('example.com/abc') == ('', '', '', '', '', '', '', 'example.com/abc', '', '', 'example.com/abc')
    assert parse('www.example.com') == ('', '', '', '', '', '', '', 'www.example.com', '', '', 'www.example.com')
    assert parse('www.example.com/?x=1') == ('', '', '', '', '', '', '', 'www.example.com/', 'x=1', '', 'www.example.com/?x=1')
    assert parse('www.example.com?x=1') == ('', '', '', '', '', '', '', 'www.example.com', 'x=1', '', 'www.example.com?x=1')
    assert parse('www.example.com/#foo') == ('', '', '', '', '', '', '', 'www.example.com/', '', 'foo', 'www.example.com/#foo')
    assert parse('www.example.com#foo') == ('', '', '', '', '', '', '', 'www.example.com', '', 'foo', 'www.example.com#foo')


def test_parse__ip():
    assert parse('http://[::1]/foo') == ('http', '', '', '', '[::1]', '', '', '/foo', '', '', 'http://[::1]/foo')
    assert parse('[::1]/foo') == ('', '', '', '', '', '', '', '[::1]/foo', '', '', '[::1]/foo')


def test_extract():
    assert extract('http://example.com') == ('http', '', '', '', 'example', 'com', '', '', '', '', 'http://example.com')
    assert extract('http://example.com:8080') == ('http', '', '', '', 'example', 'com', '8080', '', '', '', 'http://example.com:8080')
    assert extract('http://example.com:8080/abc?x=1&y=2#qwe') == ('http', '', '', '', 'example', 'com', '8080', '/abc', 'x=1&y=2', 'qwe', 'http://example.com:8080/abc?x=1&y=2#qwe')
    assert extract('http://example.ac.at') == ('http', '', '', '', 'example', 'ac.at', '', '', '', '', 'http://example.ac.at')
    assert extract('http://example.co.uk/') == ('http', '', '', '', 'example', 'co.uk', '', '/', '', '', 'http://example.co.uk/')
    assert extract('http://foo.bar.example.co.uk') == ('http', '', '', 'foo.bar', 'example', 'co.uk', '', '', '', '', 'http://foo.bar.example.co.uk')
    assert extract('http://foo:bar@www.example.com:1234/foo/?x=1#bla') == ('http', 'foo', 'bar', 'www', 'example', 'com', '1234', '/foo/', 'x=1', 'bla', 'http://foo:bar@www.example.com:1234/foo/?x=1#bla')
    assert extract('http://example.com?x=y:z') == ('http', '', '', '', 'example', 'com', '', '', 'x=y:z', '', 'http://example.com?x=y:z')
    assert extract('http://example.com?x=y:z/') == ('http', '', '', '', 'example', 'com', '', '', 'x=y:z/', '', 'http://example.com?x=y:z/')

    assert extract('mailto:foo@bar.com') == ('mailto', 'foo', '', '', 'bar', 'com', '', '', '', '', 'mailto:foo@bar.com')


def test_extract__idn():
    assert extract(u'http://пример.рф') == ('http', '', '', '', u'пример', u'рф', '', '', '', '', u'http://пример.рф')
    assert extract(u'http://إختبار.مصر/') == ('http', '', '', '', u'إختبار', u'مصر', '', '/', '', '', u'http://إختبار.مصر/')


def test_extract__no_scheme():
    assert extract('example.com.') == ('', '', '', '', 'example', 'com', '', '', '', '', 'example.com.')
    assert extract('example.com/abc') == ('', '', '', '', 'example', 'com', '', '/abc', '', '', 'example.com/abc')
    assert extract('www.example.com') == ('', '', '', 'www', 'example', 'com', '', '', '', '', 'www.example.com')
    assert extract('example.com/') == ('', '', '', '', 'example', 'com', '', '/', '', '', 'example.com/')
    assert extract('example.com:8080') == ('', '', '', '', 'example', 'com', '8080', '', '', '', 'example.com:8080')
    assert extract('example.com:8080/') == ('', '', '', '', 'example', 'com', '8080', '/', '', '', 'example.com:8080/')
    assert extract('example.com:8080/abc') == ('', '', '', '', 'example', 'com', '8080', '/abc', '', '', 'example.com:8080/abc')
    assert extract('www.example.com/?x=1') == ('', '', '', 'www', 'example', 'com', '', '/', 'x=1', '', 'www.example.com/?x=1')
    assert extract('www.example.com?x=1') == ('', '', '', 'www', 'example', 'com', '', '', 'x=1', '', 'www.example.com?x=1')
    assert extract('www.example.com/#foo') == ('', '', '', 'www', 'example', 'com', '', '/', '', 'foo', 'www.example.com/#foo')
    assert extract('www.example.com#foo') == ('', '', '', 'www', 'example', 'com', '', '', '', 'foo', 'www.example.com#foo')


def test_extract__ip():
    assert extract('http://[::1]/foo') == ('http', '', '', '', '[::1]', '', '', '/foo', '', '', 'http://[::1]/foo')
    assert extract('[::1]/foo') == ('', '', '', '', '[::1]', '', '', '/foo', '', '', '[::1]/foo')


def test_clean_netloc():
    assert _clean_netloc('example.com.') == 'example.com'
    assert _clean_netloc('example.com:') == 'example.com'
    assert _clean_netloc('fOO.baR.exaMPle.com') == 'foo.bar.example.com'


def test_clean_netloc__idn():
    assert _clean_netloc(u'ПриМЕр.Рф') == u'пример.рф'


def test_split():
    assert split('http://www.example.com') == ('http', 'www.example.com', '', '', '')
    assert split('http://www.example.com/') == ('http', 'www.example.com', '/', '', '')
    assert split('http://www.example.com/abc') == ('http', 'www.example.com', '/abc', '', '')

    assert split('http://www.example.com:80') == ('http', 'www.example.com:80', '', '', '')
    assert split('http://www.example.com:8080/abc') == ('http', 'www.example.com:8080', '/abc', '', '')

    assert split('http://www.example.com/?x=1') == ('http', 'www.example.com', '/', 'x=1', '')
    assert split('http://www.example.com/abc?x=1&y=2') == ('http', 'www.example.com', '/abc', 'x=1&y=2', '')

    assert split('http://www.example.com/abc#foo') == ('http', 'www.example.com', '/abc', '', 'foo')
    assert split('http://www.example.com/abc?x=1&y=2#foo') == ('http', 'www.example.com', '/abc', 'x=1&y=2', 'foo')

    assert split('http://example.com?foo') == ('http', 'example.com', '', 'foo', '')
    assert split('http://example.com/?foo') == ('http', 'example.com', '/', 'foo', '')
    assert split('http://example.com/#foo') == ('http', 'example.com', '/', '', 'foo')
    assert split('http://example.com#foo') == ('http', 'example.com', '', '', 'foo')
    assert split('http://example.com?foo#bar') == ('http', 'example.com', '', 'foo', 'bar')
    assert split('http://example.com/#foo?bar') == ('http', 'example.com', '/', '', 'foo?bar')

    assert split('mailto:foo@bar.com') == ('mailto', 'foo@bar.com', '', '', '')


def test_split__no_scheme():
    # no scheme -> everything until query is path
    assert split('example.com') == ('', '', 'example.com', '', '')
    assert split('example.com.') == ('', '', 'example.com.', '', '')
    assert split('www.example.com') == ('', '', 'www.example.com', '', '')
    assert split('www.example.com/abc') == ('', '', 'www.example.com/abc', '', '')
    assert split('www.example.com:8080') == ('', '', 'www.example.com:8080', '', '')
    assert split('www.example.com:8080/abc') == ('', '', 'www.example.com:8080/abc', '', '')
    assert split('www.example.com:8080/abc?x=1') == ('', '', 'www.example.com:8080/abc', 'x=1', '')
    assert split('www.example.com:8080/abc#foo') == ('', '', 'www.example.com:8080/abc', '', 'foo')


def test_split__path_only():
    assert split('foo/bar') == ('', '', 'foo/bar', '', '')
    assert split('/foo/bar') == ('', '', '/foo/bar', '', '')


def test_split__ip4():
    assert split('http://192.168.1.1/') == ('http', '192.168.1.1', '/', '', '')
    assert split('http://192.168.1.1:8080/') == ('http', '192.168.1.1:8080', '/', '', '')
    assert split('192.168.1.1') == ('', '', '192.168.1.1', '', '')


def test_split__ip6():
    assert split('http://[::1]/') == ('http', '[::1]', '/', '', '')
    assert split('http://[::1]:8080/') == ('http', '[::1]:8080', '/', '', '')
    assert split('[::1]') == ('', '', '[::1]', '', '')
    assert split('[::1]:8080') == ('', '', '[::1]:8080', '', '')
    assert split('[::ffff:127.0.0.1]:8080') == ('', '', '[::ffff:127.0.0.1]:8080', '', '')


def test_split_netloc():
    assert split_netloc('example') == ('', '', 'example', '')
    assert split_netloc('example.com') == ('', '', 'example.com', '')
    assert split_netloc('www.example.com') == ('', '', 'www.example.com', '')

    assert split_netloc('example.com:80') == ('', '', 'example.com', '80')
    assert split_netloc('localhost:8080') == ('', '', 'localhost', '8080')
    assert split_netloc('foo.bar.example.com:8888') == ('', '', 'foo.bar.example.com', '8888')
    assert split_netloc('foo:bar@www.example.com:8080') == ('foo', 'bar', 'www.example.com', '8080')


def test_split_netloc__ip4():
    assert split_netloc('192.168.1.1') == ('', '', '192.168.1.1', '')
    assert split_netloc('192.168.1.1:8080') == ('', '', '192.168.1.1', '8080')
    assert split_netloc('foo:bar@192.168.1.1:8080') == ('foo', 'bar', '192.168.1.1', '8080')


def test_split_netloc__ip6():
    assert split_netloc('[::1]') == ('', '', '[::1]', '')
    assert split_netloc('[::1]:8080') == ('', '', '[::1]', '8080')
    assert split_netloc('[2001:0db8:0000:08d3:0000:8a2e:0070:7344]') == ('', '', '[2001:0db8:0000:08d3:0000:8a2e:0070:7344]', '')
    assert split_netloc('[2001:db8:0:8d3:0:8a2e:70:7344]') == ('', '', '[2001:db8:0:8d3:0:8a2e:70:7344]', '')
    assert split_netloc('[::ffff:7f00:1]') == ('', '', '[::ffff:7f00:1]', '')
    assert split_netloc('[::ffff:127.0.0.1]') == ('', '', '[::ffff:127.0.0.1]', '')
    assert split_netloc('[::ffff:127.0.0.1]:8080') == ('', '', '[::ffff:127.0.0.1]', '8080')
    assert split_netloc('foo:bar@[::1]:8080') == ('foo', 'bar', '[::1]', '8080')


def test_split_host():
    assert split_host('example.com') == ('', 'example', 'com')
    assert split_host('www.example.com') == ('www', 'example', 'com')
    assert split_host('www.foo.bar.example.com') == ('www.foo.bar', 'example', 'com')
    assert split_host('example.ac.at') == ('', 'example', 'ac.at')

    assert split_host('example.jp') == ('', 'example', 'jp')
    assert split_host('foo.kyoto.jp') == ('', 'foo', 'kyoto.jp')

    assert split_host('foo.co.uk') == ('', 'foo', 'co.uk')
    assert split_host('foo.bar.co.uk') == ('foo', 'bar', 'co.uk')
    assert split_host('parliament.uk') == ('', 'parliament', 'uk')
    assert split_host('foo.parliament.uk') == ('foo', 'parliament', 'uk')

    assert split_host('example.gs.aa.no') == ('', 'example', 'gs.aa.no')


def test_split_host__wildcard():
    assert split_host('foo.co.sch.uk') == ('', 'foo', 'co.sch.uk')


def test_split_host__exception():
    assert split_host('foo.bar.kobe.jp') == ('', 'foo', 'bar.kobe.jp')
    assert split_host('city.kobe.jp') == ('', 'city', 'kobe.jp')


def test_split_host__idn():
    assert split_host(u'例子.中国') == ('', u'例子', u'中国')
    assert split_host(u'உதாரணம்.இந்தியா') == ('', u'உதாரணம்', u'இந்தியா')


def test_split_host__ip():
    assert split_host('192.168.1.1') == ('', '192.168.1.1', '')
    assert split_host('[::1]') == ('', '[::1]', '')
