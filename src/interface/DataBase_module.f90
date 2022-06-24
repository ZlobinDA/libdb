!
!
module dataBase_module
 implicit none


 interface

  ! ��������� �������, ��������������� ���������� � ����� ������.
  subroutine openDataBase(dataBasePath) bind (C, name = "openDataBase")
   use iso_c_binding, only: c_char
   implicit none
   character(c_char) :: dataBasePath
  end subroutine openDataBase

  ! ��������� �������, ��������� ������� � ���� ������.
  subroutine makeTableInDataBase(dataBaseName, tableName) bind (C, name = "makeTableInDataBase")
   use iso_c_binding, only: c_char
   implicit none
   character(c_char) :: dataBaseName, tableName
  end subroutine makeTableInDataBase

  ! ��������� �������, ����������� ������ � ������� ���� ������.
  subroutine insertArrayInDataBase(array, size1, size2, size3, dataBaseName, tableName) bind (C, name = "insertArrayInDataBase")
   use iso_c_binding, only: c_char, c_size_t, c_float
   implicit none
   character(c_char) :: dataBaseName, tableName
   integer(c_size_t), value :: size1, size2, size3
   real(c_float), dimension(size1, size2, size3) :: array
  end subroutine insertArrayInDataBase

  ! ��������� �������, ����������� ���������� � ����� ������.
  subroutine closeDataBase(dataBasePath) bind (C, name = "closeDataBase")
   use iso_c_binding, only: c_char
   implicit none
   character(c_char) :: dataBasePath
  end subroutine closeDataBase

 end interface


 contains

 !** ���������� ��������� ����������� �����
 function c_message(message)
  implicit none
  character(len = *), intent(in) :: message
  character(len = len(message) + 1) :: c_message
  c_message = trim(message) // char(0)
  return
 end function c_message

end module dataBase_module