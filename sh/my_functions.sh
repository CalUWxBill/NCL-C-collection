
get_array_idx () {
    local array="$1[@]"
    local seeking=$2
    local cnt=0
    for element in "${!array}"; do
#       echo "element="$element" seeking="$seeking
        if [[ $element == $seeking ]]; then
            break
        fi
        ((cnt++))
    done
    return $cnt
}
