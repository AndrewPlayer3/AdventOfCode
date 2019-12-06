Program DAY_ONE
    PRINT *, "Hello, Day 1"
    OPEN(10, file="input.txt")
    READ(unit=10,fmt=*) str
    PRINT *, str
End Program DAY_ONE