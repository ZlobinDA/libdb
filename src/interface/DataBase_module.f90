!
! Интерфейсы функция для работы с базой данных.
module dataBase_module
 implicit none

 interface

  ! Копирование массива в структуры данных оболочки.
  subroutine shell_sendSingleDimensionArray(array, size, name) bind (C, name = "shell_sendSingleDimensionArray")
   use iso_c_binding, only: c_size_t, c_float, c_char
   implicit none
   character(c_char) :: name
   integer(c_size_t), value :: size
   real(c_float), dimension(size) :: array
  end subroutine shell_sendSingleDimensionArray

  ! Добавление новых данных расчета в базу данных.
  subroutine dataBase_insertData(dataBasePath) bind (C, name = "dataBase_insertData")
   use iso_c_binding, only: c_char
   implicit none
   character(c_char) :: dataBasePath
  end subroutine dataBase_insertData

 end interface

end module dataBase_module