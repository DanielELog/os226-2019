
set -o pipefail

cmpout() {
	local base=$1
	shift 1

	"$@" < $base.in | diff -u $base.out -
}

testouts() {
	local base=$1
	shift 1

	local ret=0
	for i in $base/*.in; do
		cmpout ${i%%.in} "$@" || ret=1
	done

	return $ret
}
