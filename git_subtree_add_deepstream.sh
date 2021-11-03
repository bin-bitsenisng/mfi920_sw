# https://blog.rhostem.com/posts/2020-01-03-code-sharing-with-git-subtree

REMOTE=deepstream-lib
REMOTE_URL=git@github.bts:bitsensing/deepstream.git
BRANCH=master
SUBDIR=axx910_sw/Source/ASW/Vision/deepstream

mkdir -p $SUBDIR
git remote add $REMOTE $REMOTE_URL
git subtree add --squash --prefix $SUBDIR $REMOTE $BRANCH
