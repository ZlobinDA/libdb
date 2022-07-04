!
! Имитация расчетной модели
subroutine model() bind (C, name = "model")

 use dataBase_module, only: dataBase_open, dataBase_close, & 
    dataBase_makeThreeDimensionTable, dataBase_insertThreeDimensionArray, & 
    dataBase_makeTwoDimensionTable, dataBase_insertTwoDimensionArray, & 
    dataBase_makeSingleDimensionTable, dataBase_insertSingleDimensionArray
 use env_module, only: c_message

 implicit none
 integer(4), parameter :: small_1DimensionSize = 2
 integer(4), parameter :: small_2DimensionSize = 2
 integer(4), parameter :: small_3DimensionSize = 2
 real(4) :: small_array(small_1DimensionSize, small_2DimensionSize, small_3DimensionSize)

 integer(4), parameter :: big_1DimensionSize = 37
 integer(4), parameter :: big_2DimensionSize = 163
 integer(4), parameter :: big_3DimensionSize = 50
 real(4) :: big_array(big_1DimensionSize, big_2DimensionSize, big_3DimensionSize)
 real(4) :: singleDimension_array(big_2DimensionSize*big_3DimensionSize)

 character(len = 32) :: tableName
 character(len = 16), parameter :: dataBasePath = "test_db.db"
 integer(4) :: i, j, k, index, index1, index2, index3
 real(4) :: value

 interface
  ! Интерфейс функция, устанавливающей соединение с базой данных.
  subroutine removeDataBase(dataBasePath) bind (C, name = "removeDataBase")
   use iso_c_binding, only: c_char
   implicit none
   character(c_char) :: dataBasePath
  end subroutine removeDataBase
 end interface

 ! Удаляем старую версию базы данных.
 call removeDataBase(c_message(dataBasePath))

!#define TEST1
! Тест 1. Запись малого объема данных.
#ifdef TEST1
 print*, "Test1. Small data"
 ! Имитация выполнение расчета
 value = 0.5
 do i = 1, small_1DimensionSize
  do j = 1, small_2DimensionSize
   do k = 1, small_3DimensionSize
    value = value + 1.0
    small_array(i, j, k) = value
   end do
  end do
 end do
 ! Запись результатов в БД

 call dataBase_open(c_message(dataBasePath))
 tableName = "smallData"
 call dataBase_makeThreeDimensionTable(c_message(dataBasePath), c_message(tableName))
 call dataBase_insertThreeDimensionArray(small_array, small_1DimensionSize, small_2DimensionSize, small_3DimensionSize, c_message(dataBasePath), c_message(tableName))
 call dataBase_close(c_message(dataBasePath))
#endif

!#define TEST2
! Тест 2. Запись малого объема данных. Рандомные значения.
#ifdef TEST2
 print*, "Test2. Big data"
 ! Имитация выполнение расчета
 value = 0.5
 do i = 1, big_1DimensionSize
  do j = 1, big_2DimensionSize
   do k = 1, big_3DimensionSize
    value = value + 1.0
    big_array(i, j, k) = value
   end do
  end do
 end do
 ! Запись результатов в БД
 call dataBase_open(c_message(dataBasePath))
 tableName = "bigData"
 call dataBase_makeThreeDimensionTable(c_message(dataBasePath), c_message(tableName))
 call dataBase_insertThreeDimensionArray(big_array, big_1DimensionSize, big_2DimensionSize, big_3DimensionSize, c_message(dataBasePath), c_message(tableName))
 call dataBase_close(c_message(dataBasePath))
#endif

!#define TEST3
! Тест 3. Запись двумерного массива данных. Рандомные значения.
#ifdef TEST3
 print*, "Test3. Two dimension array"
 ! Имитация выполнение расчета
 value = 0.5
 do j = 1, big_3DimensionSize
  do k = 1, big_2DimensionSize
   value = value + 1.0
   index = k + big_2DimensionSize*(j - 1)
   singleDimension_array(index) = value
  end do
 end do
 ! Запись результатов в БД
 call dataBase_open(c_message(dataBasePath))
 tableName = "twoDimension"
 call dataBase_makeTwoDimensionTable(c_message(dataBasePath), c_message(tableName))
 index1 = big_2DimensionSize
 index2 = big_3DimensionSize
 call dataBase_insertTwoDimensionArray(singleDimension_array, index1, index2, c_message(dataBasePath), c_message(tableName))
 call dataBase_close(c_message(dataBasePath))
#endif

!****************************************************************************************
! Тест 4. Запись одномерного массива данных. Рандомные значения.
#define TEST4
!****************************************************************************************
#ifdef TEST4
 print*, "Test4. Single dimension array"
 ! Имитация выполнение расчета
 value = 0.5
 do j = 1, big_3DimensionSize
  do k = 1, big_2DimensionSize
   value = value + 1.0
   index = k + big_2DimensionSize*(j - 1)
   singleDimension_array(index) = value
  end do
 end do
 ! Запись результатов в БД
 call dataBase_open(c_message(dataBasePath))
 tableName = "singleDimension"
 call dataBase_makeSingleDimensionTable(c_message(dataBasePath), c_message(tableName))
 index1 = big_2DimensionSize * big_3DimensionSize
 call dataBase_insertSingleDimensionArray(singleDimension_array, index1, c_message(dataBasePath), c_message(tableName))
 call dataBase_close(c_message(dataBasePath))
#endif

 return
end subroutine model