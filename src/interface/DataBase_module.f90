!
!
module dataBase_module
 implicit none


 interface

  ! ��������� �������, ��������������� ���������� � ����� ������.
  subroutine dataBase_open(dataBasePath) bind (C, name = "dataBase_open")
   use iso_c_binding, only: c_char
   implicit none
   character(c_char) :: dataBasePath
  end subroutine dataBase_open

  ! ��������� �������, ��������� ���������� ������� � ���� ������.
  subroutine dataBase_makeThreeDimensionTable(dataBaseName, tableName) bind (C, name = "dataBase_makeThreeDimensionTable")
   use iso_c_binding, only: c_char
   implicit none
   character(c_char) :: dataBaseName, tableName
  end subroutine dataBase_makeThreeDimensionTable

  ! ��������� �������, ��������� ���������� ������� � ���� ������.
  subroutine dataBase_makeTwoDimensionTable(dataBaseName, tableName) bind (C, name = "dataBase_makeTwoDimensionTable")
   use iso_c_binding, only: c_char
   implicit none
   character(c_char) :: dataBaseName, tableName
  end subroutine dataBase_makeTwoDimensionTable

  ! ��������� �������, ����������� ������ � ���������� ������� ���� ������.
  subroutine dataBase_insertThreeDimensionArray(array, size1, size2, size3, dataBaseName, tableName) bind (C, name = "dataBase_insertThreeDimensionArray")
   use iso_c_binding, only: c_char, c_size_t, c_float
   implicit none
   character(c_char) :: dataBaseName, tableName
   integer(c_size_t), value :: size1, size2, size3
   real(c_float), dimension(size1, size2, size3) :: array
  end subroutine dataBase_insertThreeDimensionArray

  ! ��������� �������, ����������� ������ � ���������� ������� ���� ������.
  subroutine dataBase_insertTwoDimensionArray(array, size1, size2, dataBaseName, tableName) bind (C, name = "dataBase_insertTwoDimensionArray")
   use iso_c_binding, only: c_char, c_size_t, c_float
   implicit none
   character(c_char) :: dataBaseName, tableName
   integer(c_size_t), value :: size1, size2
   real(c_float), dimension(size1, size2) :: array
  end subroutine dataBase_insertTwoDimensionArray

  ! ��������� �������, ����������� ���������� � ����� ������.
  subroutine dataBase_close(dataBasePath) bind (C, name = "dataBase_close")
   use iso_c_binding, only: c_char
   implicit none
   character(c_char) :: dataBasePath
  end subroutine dataBase_close

 end interface

end module dataBase_module