#!/bin/bash

workdir=$(dirname $(realpath -- $0))
target="${workdir}/spider"
release="${workdir}/common/debug_release.go"

cd "${workdir}"

cat > "${release}" << EOF
package common

const  TAG      string = "spider-online"

EOF

go build 

cat > "${release}" << EOF
package common

const  TAG      string = "spider"

EOF

scp "${target}" "dingjing@172.30.50.200:/data/bin/"

rm -rf "${target}"





