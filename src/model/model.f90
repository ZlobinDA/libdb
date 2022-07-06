!
! �������� ��������� ������
subroutine model() bind (C, name = "model")
 use env_module, only: c_message

 implicit none
 character(len = 16), parameter :: dataBaseName = "test_db.db"

 interface
  ! ��������� �������, ��������������� ���������� � ����� ������.
  subroutine removeDataBase(dataBaseName) bind (C, name = "removeDataBase")
   use iso_c_binding, only: c_char
   implicit none
   character(c_char) :: dataBaseName
  end subroutine removeDataBase
 end interface

 ! ������� ������ ������ ���� ������.
 call removeDataBase(c_message(dataBaseName))

!****************************************************************************************
! ���� 1. 
!#define TEST1
!****************************************************************************************
#ifdef TEST1
 call test1(dataBaseName)
#endif

!****************************************************************************************
! ���� 2.
!#define TEST2
!****************************************************************************************
#ifdef TEST2
 call test2(dataBaseName)
#endif 

!****************************************************************************************
! ���� 3.
#define TEST3
!****************************************************************************************
#ifdef TEST3
 call test3(dataBaseName)
#endif 
 return
end subroutine model