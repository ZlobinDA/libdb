!
!
module dataBase_module
 implicit none

 interface

  subroutine openDataBase(dataBasePath) bind (C, name = "openDataBase")
   use iso_c_binding, only: c_char
   implicit none
   character(c_char) :: dataBasePath
  end subroutine openDataBase

  subroutine insert_dataBase(dataBaseName, index1, index2, index3, value) bind (C, name = "insert_dataBase")
   use iso_c_binding, only: c_size_t, c_float
   implicit none
   integer(c_size_t), value :: dataBaseName, index1, index2, index3
   real(c_float), value :: value
  end subroutine insert_dataBase
 end interface

 contains

 !** ƒополнение сообщени€ завершающим нулем
 function c_message(message)
  implicit none
  character(len = *), intent(in) :: message
  character(len = len(message) + 1) :: c_message
  c_message = trim(message) // char(0)
  return
 end function c_message

end module dataBase_module