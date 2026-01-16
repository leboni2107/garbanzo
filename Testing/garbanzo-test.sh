#!/bin/bash

ITERATIONS=${1:-10}

help=$(../cmake-build-debug/garbanzo --help 2>&1)
declare -a args

while IFS= read -r line; do
  if [[ $line =~ ^-[a-z][[:space:]]+--([a-z-]+) ]]; then
    arg="${BASH_REMATCH[1]}"

    if [[ "$arg" != "help" && "$arg" != "version" ]]; then
      args+=("$arg")
    fi
  fi
done <<< "$help"

max_combinations=$((1 << ${#args[@]}))

echo "$max_combinations Combinations to test (${ITERATIONS} iterations each)"
echo ""

for ((i = 0; i < max_combinations; i++)); do
  cmd_args=""

  for ((j = 0; j < ${#args[@]}; j++)); do
    if((i & (1 << j))); then
      cmd_args+=" --${args[j]}"
    fi
  done;

  total_duration=0

  for ((iter = 0; iter < ITERATIONS; iter++)); do
    start=$(date +%s%6N)
    ../cmake-build-debug/garbanzo$cmd_args > /dev/null 2>&1
    end=$(date +%s%6N)
    duration=$((end - start))
    total_duration=$((total_duration + duration))
  done

  avg_duration=$((total_duration / ITERATIONS))

  echo "Combination ${i}: ${avg_duration}μs (avg of ${ITERATIONS}) | ${cmd_args}"

done;