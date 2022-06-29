!
!
module env_module
 implicit none

 contains

 !** ƒополнение сообщени€ завершающим нулем
 function c_message(message)
  implicit none
  character(len = *), intent(in) :: message
  character(len = len(message) + 1) :: c_message
  c_message = trim(message) // char(0)
  return
 end function c_message

end module env_module
 