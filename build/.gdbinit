define pt
    if $argc != 2
        echo need arg
    else
        printf "index: values\n"
        set $i=0
        while($i < $arg1)
            printf "%d: ", $i
            set $j=ht.table[$i]
                while($j.next != 0)
                    printf "%c ", $j.val
                    set $j=$j.next
                end
                printf "%c\n", $j.val
            set $i=$i+1
        end
    end
end
