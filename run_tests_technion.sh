for i  in {0..29}
  do  ./main < "sub1_tests/randtest$i.in" > "sub1_tests/ours/randtest$i.out"; diff "sub1_tests/ours/randtest$i.out"  "sub1_tests/randtest$i.out"; echo $i;
done


#for i  in {0..29}
#  do valgrind --leak-check=full  ./main < "tests/wacky/in/input$i.in" > "tests/wacky/real-out/output$i.out"
#done