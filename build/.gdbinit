define pt
    if $argc != 1
        printf "need arg\n"
    else
        printf "buckets: %d\n", $arg0.m_bucket_count
        printf "size: %d\n", $arg0.m_size
        printf "index: values\n"
        set $i=0
        while($i < $arg0.m_capacity)
            printf "%d: ", $i
            set $j=$arg0.m_table[$i]
                if($j)
                    while($j.next)
                        printf "(%d,%d) ", $j.key, $j.val
                        set $j=$j.next
                    end
                    printf "(%d,%d) ", $j.key, $j.val
                end
                printf "\n"
            set $i=$i+1
        end
    end
end
