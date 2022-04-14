add_llvm_library( LLVMFuncBlockCount MODULE
  FuncBlockCount.cpp

  PLUGIN_TOOL
  opt
  )
