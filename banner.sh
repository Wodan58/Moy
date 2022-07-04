#
#   module  : banner.sh
#   version : 1.2
#   date    : 06/16/22
#
#   Announce project creation
#
echo Updating $1 version $2
lcov --version
lcov --directory . --zerocounters
