add_llvm_library( LLVMCountopcodes MODULE
  CountOp.cpp

  PLUGIN_TOOL
  opt
  )
