!
! Имитация расчетной модели
subroutine model() bind (C, name = "model")

 use dataBase_module, only: openDataBase, makeTableInDataBase, insertArrayInDataBase, closeDataBase, c_message

 implicit none
 integer(4), parameter :: small_1DimensionSize = 2
 integer(4), parameter :: small_2DimensionSize = 2
 integer(4), parameter :: small_3DimensionSize = 2
 real(4) :: small_array(small_1DimensionSize, small_2DimensionSize, small_3DimensionSize)

 integer(4), parameter :: big_1DimensionSize = 37
 integer(4), parameter :: big_2DimensionSize = 163
 integer(4), parameter :: big_3DimensionSize = 50
 real(4) :: big_array(big_1DimensionSize, big_2DimensionSize, big_3DimensionSize)

 character(len = 32) :: tableName
 character(len = 16), parameter :: dataBasePath = "test_db.db"
 integer(4) :: i, j, k
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

#define TEST1
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

 call openDataBase(c_message(dataBasePath))
 tableName = "smallData"
 call makeTableInDataBase(c_message(dataBasePath), c_message(tableName))
 call insertArrayInDataBase(small_array, small_1DimensionSize, small_2DimensionSize, small_3DimensionSize, c_message(dataBasePath), c_message(tableName))
 call closeDataBase(c_message(dataBasePath))
#endif

#define TEST2
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
 call openDataBase(c_message(dataBasePath))
 tableName = "bigData"
 call makeTableInDataBase(c_message(dataBasePath), c_message(tableName))
 call insertArrayInDataBase(big_array, big_1DimensionSize, big_2DimensionSize, big_3DimensionSize, c_message(dataBasePath), c_message(tableName))
 call closeDataBase(c_message(dataBasePath))
#endif

 return
end subroutine model