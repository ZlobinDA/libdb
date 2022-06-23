!
! �������� ��������� ������
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
! ���� 1. ������ ������ ������ ������. ��� �������� ����������.
#ifdef TEST1
 ! �������� ���������� �������
 value = 7.0
 do i = 1, test1_1DimensionSize
  do j = 1, test1_2DimensionSize
   do k = 1, test1_3DimensionSize
    test1_array(i, j, k) = value
   end do
  end do
 end do
 
 ! ������ ����������� � ��
 dataBasePath = "test1_db.db"
 call openDataBase(c_message(dataBasePath))
 ! call insert_dataBase(dataBase0, i, j, k, value)

#endif


!#define TEST2
! ���� 2. ������ ������ ������ ������. ��� �������� ������.
#ifdef TEST2
 ! �������� ���������� �������
 ! ������ ����������� � ��
#endif

 return
end subroutine model