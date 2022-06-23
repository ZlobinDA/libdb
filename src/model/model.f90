!
! Имитация расчетной модели
subroutine model() bind (C, name = "model")

 use dataBase_module, only: openDataBase, insert_dataBase, c_message

 implicit none
 integer(4), parameter :: test1_1DimensionSize = 2
 integer(4), parameter :: test1_2DimensionSize = 2
 integer(4), parameter :: test1_3DimensionSize = 2
 real(4) :: test1_array(test1_1DimensionSize, test1_2DimensionSize, test1_3DimensionSize)

 integer(4), parameter :: test2_1DimensionSize = 37
 integer(4), parameter :: test2_2DimensionSize = 163
 integer(4), parameter :: test2_3DimensionSize = 50
 real(4) :: test2_array(test2_1DimensionSize, test2_2DimensionSize, test2_3DimensionSize)

 character(len = 64) :: dataBasePath
 integer(4) :: i, j, k
 real(4) :: value

#define TEST1
! Тест 1. Запись малого объема данных. Все значения одинаковые.
#ifdef TEST1
 ! Имитация выполнение расчета
 value = 7.0
 do i = 1, test1_1DimensionSize
  do j = 1, test1_2DimensionSize
   do k = 1, test1_3DimensionSize
    test1_array(i, j, k) = value
   end do
  end do
 end do
 
 ! Запись результатов в БД
 dataBasePath = "test1_db.db"
 call openDataBase(c_message(dataBasePath))
 ! call insert_dataBase(dataBase0, i, j, k, value)

#endif


!#define TEST2
! Тест 2. Запись малого объема данных. Все значения разные.
#ifdef TEST2
 ! Имитация выполнение расчета
 ! Запись результатов в БД
#endif

 return
end subroutine model