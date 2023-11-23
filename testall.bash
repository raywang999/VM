cd tests
for testdir in $(ls); do 
  cd $testdir
  echo $testdir
  make
  make check
  cd ..
cd ..
done
