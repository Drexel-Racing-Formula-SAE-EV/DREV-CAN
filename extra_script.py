Import('env')

platform = env.get('PIOPLATFORM')

platform_map = {
    'atmelavr': 'arduino'
}

if platform in platform_map.keys():
    platform = platform_map[platform]

env.Append(SRC_FILTER=["+<drev-can-common>", "+<drev-can-{}>".format(platform)])
