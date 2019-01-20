define pt
    if $argc != 2
        echo need arg
    else
        printf "index: values\n"
        set $i=0
        while($i < $arg1)
            printf "%d: ", $i
            set $j=ht.table[$i]
                if($j)
                    while($j.next)
                        printf "(%c,%c) ", $j.key, $j.val
                        set $j=$j.next
                    end
                    printf "(%c,%c) ", $j.key, $j.val
                end
                printf "\n"
            set $i=$i+1
        end
    end
end
