!
! Тест 3.
subroutine test3(dataBaseName)

 use dataBase_module, only: shell_sendSingleDimensionArray, dataBase_insertData
 use env_module, only: c_message

 implicit none
 character(len  = 2) :: tableNumber
 character(len = 16) :: NAMA, NMVAR
 character(len = 16), intent(in) :: dataBaseName
 integer(4), parameter :: dimension1 = 37
 integer(4), parameter :: dimension2 = 163
 integer(4), parameter :: dimension3 = 50
 integer(4), parameter :: dimension4 = 398
 integer(4), parameter :: nTables = 1

 real(4), allocatable :: array(:)

 character(len = 16) :: tableName
 integer(4) :: i, j, k, index, size, IDB, IER
 real(4) :: value, startTimePoint, finishTimePoint

 print*, "Test3. Big arrays multi inserting"
 size = dimension1*dimension2*dimension3*dimension4
 if (allocated(array)) then
  deallocate(array)
  allocate(array(size))
  array = 0.0
 else
  allocate(array(size))
  array = 0.0
 end if
 ! Заполняем массив данными.
 print*, "Test3. Make array with dimension: ", size
 value = 0.5
 index = 0
 do i = 1, size
  value = value + 1.0
  index = index + 1
  array(index) = value
 end do

 !---------------------------------------------------------------------------------------
 ! Запись базы данных с помощью sqlite
 !---------------------------------------------------------------------------------------
 ! Записываем массив в количестов таблиц равное nTables
 print*, "Test3. Send arrays to the shell"
 do i = 1, nTables
  print*, "Test3. Send array: ", i
  write(tableNumber, "(i2.2)") i
  tableName = "Table" // tableNumber
  call shell_sendSingleDimensionArray(array, size, c_message(tableName))
 end do
 
 print*, "Test3. Insert data in a sqlite data base. Start time duration calculation"
 call CPU_TIME(startTimePoint)
 
 call dataBase_insertData(c_message(dataBaseName))
 
 call CPU_TIME(finishTimePoint)
 print*, "Test3. Time of inserting data in a sqlite data base: ", (finishTimePoint - startTimePoint), " s"

 !---------------------------------------------------------------------------------------
 ! Запись базы данных с помощью файла прямого доступа
 !---------------------------------------------------------------------------------------
 print*, "Test3. Insert data in am inifs data base. Start time duration calculation"
 call CPU_TIME(startTimePoint)

 call inifs()
 NMVAR = "inifs.db"
 IDB = 1
 CALL CREFS(NMVAR, 25, IDB)
 CALL OPEFS(NMVAR, 25, IDB)
 NAMA="test"
 CALL WRARR(NAMA, IDB, array, size, IER)

 call CPU_TIME(finishTimePoint)
 print*, "Test3. Time of inserting data in an inifs data base: ", (finishTimePoint - startTimePoint), " s"

 return
end subroutine test3