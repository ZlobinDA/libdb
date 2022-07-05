!
! Тест 1.
subroutine test1(dataBaseName)

 use dataBase_module, only: shell_sendSingleDimensionArray, dataBase_insertData
 use env_module, only: c_message

 implicit none
 character(len = 16), intent(in) :: dataBaseName
 integer(4), parameter :: dimension1 = 2
 integer(4), parameter :: dimension2 = 2

 real(4), allocatable :: array(:)

 character(len = 16) :: arrayName
 integer(4) :: i, j, index, size
 real(4) :: value

 print*, "Test1. Single array inserting"
 ! Имитация выполнение расчета
 if (allocated(array)) then
  deallocate(array)
  allocate(array(dimension2*dimension2))
  array = 0.0
 else
  allocate(array(dimension2*dimension2))
  array = 0.0
 end if
 value = 0.5
 do j = 1, dimension2
  do i = 1, dimension2
   value = value + 1.0
   index = i + dimension2*(j - 1)
   array(index) = value
  end do
 end do

 size = dimension2 * dimension2
 arrayName = "firstArray"
 call shell_sendSingleDimensionArray(array, size, c_message(arrayName))

 call dataBase_insertData(c_message(dataBaseName))

 return
end subroutine test1