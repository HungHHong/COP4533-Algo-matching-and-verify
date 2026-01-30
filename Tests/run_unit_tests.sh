##unit test for matcher and verifier
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
for f in tests/unstable/*.out; do
  vout="$(run_verifier "$f" || true)"
  echo "$vout" | grep -Eq "UNSTABLE|blocking pair" \
    && pass "unstable detected: $(basename "$f")" \
    || { echo "$vout"; fail "unstable NOT detected: $(basename "$f")"; }
done

echo "All unit tests passed."
