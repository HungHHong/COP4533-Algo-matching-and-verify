#!/usr/bin/env bash
set -euo pipefail

MATCHER="./bin/matcher"
VERIFIER="./bin/verifier"
INPUT="data/example.in"
OUTDIR="result"

mkdir -p "$OUTDIR"

# helper: run verifier on (input + matching)
run_verifier() {
  local matching_file="$1"
  ( cat "$INPUT"; echo; cat "$matching_file" ) | "$VERIFIER"
}

pass() { echo "pass $1"; }
fail() { echo "fail $1"; exit 1; }

# 0) build 
make >/dev/null
pass "build"

# 1) matcher runs + produces n lines
"$MATCHER" < "$INPUT" > "$OUTDIR/match.out" || fail "matcher crashed"
pass "matcher runs"

# Check matcher output has exactly n lines
n="$(head -n 1 "$INPUT" | tr -d '\r')"
lines="$(wc -l < "$OUTDIR/match.out" | tr -d ' ')"
if [[ "$lines" != "$n" ]]; then
  echo "Matcher output has $lines lines, expected $n"
  echo "--- output ---"
  cat "$OUTDIR/match.out"
  fail "matcher output line count"
fi
pass "matcher output line count = n"

# 2) verifier accepts matcher output 
vout="$(run_verifier "$OUTDIR/match.out" || true)"
echo "$vout" | grep -Eq "VALID STABLE|VALID" \
  && pass "verifier accepts matcher output" \
  || { echo "$vout"; fail "verifier rejected matcher output"; }

# 3) verifier rejects invalid matchings
for f in tests/invalid/*.out; do
  vout="$(run_verifier "$f" || true)"
  echo "$vout" | grep -q "INVALID" \
    && pass "invalid rejected: $(basename "$f")" \
    || { echo "$vout"; fail "invalid NOT rejected: $(basename "$f")"; }
done

# 4) verifier detects unstable matchings
# Create a valid but likely-unstable matching by swapping students of hospital 1 and 2
unstable_file="$OUTDIR/unstable_generated.out"
awk 'NR==1{a=$2; print $1" "$2; next}
     NR==2{b=$2; print $1" "a; next}
     NR==3{print "1 "b; next}
     {print}' "$OUTDIR/match.out" > "$unstable_file"

vout="$(run_verifier "$unstable_file" || true)"
echo "$vout" | grep -Eq "UNSTABLE|blocking pair|INVALID" \
  && pass "unstable detected (generated swap)" \
  || { echo "$vout"; echo "--- unstable file ---"; cat "$unstable_file"; fail "unstable NOT detected (generated swap)"; }


echo "All unit tests passed."
