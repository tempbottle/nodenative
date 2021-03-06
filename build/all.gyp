{
    'targets' : [
        #server
        {
            'target_name' : 'webserver',
            'type' : 'executable',
            'dependencies': [
                './native.gyp:node_native'
            ],
            'sources' : [
                '../samples/webserver.cpp'
            ]
        },
        #client
        {
            'target_name' : 'webclient',
            'type' : 'executable',
            'dependencies': [
                './native.gyp:node_native'
            ],
            'sources' : [
                '../samples/webclient.cpp'
            ]
        },
        #test
        {
            'target_name' : 'test',
            'type' : 'executable',
            'dependencies': [
                './native.gyp:node_native',
                './gmock.gyp:gmock_main'
            ],
            'sources' : [
                '../test/basic_test.cpp',
                '../test/crypto_test.cpp',
                '../test/fs_test.cpp',
                '../test/http/Server_test.cpp',
                '../test/http/ServerPlugin_test.cpp',
                '../test/http/encodeUrl_test.cpp',
                '../test/http/decodeUrl_test.cpp',
                '../test/timer_test.cpp',
                '../test/async_test.cpp',
                '../test/Future/then_test.cpp',
                '../test/Future/error_test.cpp',
                '../test/Future/finally_test.cpp',
                '../test/worker_test.cpp',
                '../test/UriTemplate_test.cpp',
                '../test/UriTemplateFormat_test.cpp',
                '../test/UriTemplateSimple_test.cpp',
            ]
        },
        #bechUriTemplate
        {
            'target_name' : 'benchUriTemplate',
            'type' : 'executable',
            'dependencies': [
                './native.gyp:node_native'
            ],
            'sources' : [
                '../samples/benchmarks/uriTemplate_bench.cpp'
            ]
        },
    ]
}
