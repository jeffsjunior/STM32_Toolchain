#!/usr/bin/python

import string
import sys
import os
import re
import binascii
import struct
import zlib

def gen_stm32_meminfo():

	if len(sys.argv) != 2:
		print 'Usage: gen_stm32_meminfo.exe output.sym'
		sys.exit(0)

	app_sym_file = sys.argv[1]

	fp = file(app_sym_file)
	if fp is None:
		print "open sym file error\n"
		sys.exit(0)

	lines = fp.readlines()
	fp.close()

	##--------------------------------------------------
	var_text_start_addr = None
	p = re.compile('(\w*)(\sA\s)(_ld_text_start)$')
	for line in lines:
		m = p.search(line)
		if m != None:
			var_text_start_addr = m.group(1)
			
	if var_text_start_addr == None:
		print "[ERRO] not found (_ld_text_start)\n"
		sys.exit(1)
	
	##--------------------------------------------------
	var_text_end_addr = None
	p = re.compile('(\w*)(\sA\s)(_ld_text_end)$')
	for line in lines:
		m = p.search(line)
		if m != None:
			var_text_end_addr = m.group(1)
			
	if var_text_end_addr == None:
		print "[ERRO] not found (_ld_text_end)\n"
		sys.exit(1)
	
	##--------------------------------------------------
	var_rodata_start_addr = None
	p = re.compile('(\w*)(\sA\s)(_ld_rodata_start)$')
	for line in lines:
		m = p.search(line)
		if m != None:
			var_rodata_start_addr = m.group(1)
			
	if var_rodata_start_addr == None:
		print "[ERRO] not found (_ld_rodata_start)\n"
		sys.exit(1)
	
	##--------------------------------------------------
	var_rodata_end_addr = None
	p = re.compile('(\w*)(\sA\s)(_ld_rodata_end)$')
	for line in lines:
		m = p.search(line)
		if m != None:
			var_rodata_end_addr = m.group(1)
			
	if var_rodata_end_addr == None:
		print "[ERRO] not found (_ld_rodata_end)\n"
		sys.exit(1)
	
	##--------------------------------------------------
	var_data_start_addr = None
	p = re.compile('(\w*)(\sA\s)(_ld_data_start)$')
	for line in lines:
		m = p.search(line)
		if m != None:
			var_data_start_addr = m.group(1)
			
	if var_data_start_addr == None:
		print "[ERRO] not found (_ld_data_start)\n"
		sys.exit(1)
	
	##--------------------------------------------------
	var_data_end_addr = None
	p = re.compile('(\w*)(\sA\s)(_ld_data_end)$')
	for line in lines:
		m = p.search(line)
		if m != None:
			var_data_end_addr = m.group(1)
			
	if var_data_end_addr == None:
		print "[ERRO] not found (_ld_data_end)\n"
		sys.exit(1)
	
	##--------------------------------------------------
	var_bss_start_addr = None
	p = re.compile('(\w*)(\sA\s)(_ld_bss_start)$')
	for line in lines:
		m = p.search(line)
		if m != None:
			var_bss_start_addr = m.group(1)
			
	if var_bss_start_addr == None:
		print "[ERRO] not found (_ld_bss_start)\n"
		sys.exit(1)
	
	##--------------------------------------------------
	var_bss_end_addr = None
	p = re.compile('(\w*)(\sA\s)(_ld_bss_end)$')
	for line in lines:
		m = p.search(line)
		if m != None:
			var_bss_end_addr = m.group(1)
			
	if var_bss_end_addr == None:
		print "[ERRO] not found (_ld_bss_end)\n"
		sys.exit(1)
	
	##--------------------------------------------------
	var_heap_start_addr = None
	p = re.compile('(\w*)(\sA\s)(_ld_heap_start)$')
	for line in lines:
		m = p.search(line)
		if m != None:
			var_heap_start_addr = m.group(1)
			
	if var_heap_start_addr == None:
		print "[ERRO] not found (_ld_heap_start)\n"
		sys.exit(1)
	
	##--------------------------------------------------
	var_heap_end_addr = None
	p = re.compile('(\w*)(\sA\s)(_ld_heap_end)$')
	for line in lines:
		m = p.search(line)
		if m != None:
			var_heap_end_addr = m.group(1)
			
	if var_heap_end_addr == None:
		print "[ERRO] not found (_ld_heap_end)\n"
		sys.exit(1)
	
	##--------------------------------------------------
	var_stack_start_addr = None
	p = re.compile('(\w*)(\sA\s)(_ld_stack_start)$')
	for line in lines:
		m = p.search(line)
		if m != None:
			var_stack_start_addr = m.group(1)
			
	if var_stack_start_addr == None:
		print "[ERRO] not found (_ld_stack_start)\n"
		sys.exit(1)
	
	##--------------------------------------------------
	var_stack_end_addr = None
	p = re.compile('(\w*)(\sA\s)(_ld_stack_end)$')
	for line in lines:
		m = p.search(line)
		if m != None:
			var_stack_end_addr = m.group(1)
			
	if var_stack_end_addr == None:
		print "[ERRO] not found (_ld_stack_end)\n"
		sys.exit(1)
	
	##--------------------------------------------------
	var_flash_len = None
	p = re.compile('(\w*)(\sA\s)(_ld_flash_len)$')
	for line in lines:
		m = p.search(line)
		if m != None:
			var_flash_len = m.group(1)
			
	if var_flash_len == None:
		print "[ERRO] not found (_ld_flash_len)\n"
		sys.exit(1)
	
	##--------------------------------------------------
	var_ram_len = None
	p = re.compile('(\w*)(\sA\s)(_ld_ram_len)$')
	for line in lines:
		m = p.search(line)
		if m != None:
			var_ram_len = m.group(1)
			
	if var_ram_len == None:
		print "[ERRO] not found (_ld_ram_len)\n"
		sys.exit(1)
	
	#print the information about memory
	var_text_len	= long(var_text_end_addr, 16) - long(var_text_start_addr, 16)
	var_data_len	= long(var_data_end_addr, 16) - long(var_data_start_addr, 16)
	var_rodata_len	= long(var_rodata_end_addr, 16) - long(var_rodata_start_addr, 16)
	var_bss_len		= long(var_bss_end_addr, 16) - long(var_bss_start_addr, 16)
	var_heap_len	= long(var_heap_end_addr, 16) - long(var_heap_start_addr, 16)
	var_stack_len	= long(var_stack_end_addr, 16) - long(var_stack_start_addr, 16)
	sram_usado 		= var_data_len + var_bss_len
	sram_sobra 		= long(var_ram_len, 16) - sram_usado
	flash_usado 	= var_text_len + var_rodata_len + var_data_len
	flash_sobra 	= long(var_flash_len, 16) - flash_usado
	print "============================= MEMORY INFO ============================="
	print "[.text",var_text_len,"Bytes][.rodata",var_rodata_len,"Bytes][.data",var_data_len,"Bytes][.bss",var_bss_len,"Bytes]"
	print "-----------------------------------------------------------------------"
	print "RAM (.data .bss)"
	print "[USED RAM:",sram_usado,"Bytes][FREE RAM:",sram_sobra,"Bytes]"
	print "-----------------------------------------------------------------------"
	print "FLASH (.text .rodata .data)"
	print "[USED FLASH:",flash_usado,"Bytes][FREE FLASH:",flash_sobra,"Bytes]"
	print "-----------------------------------------------------------------------"
	print "[heap size",var_heap_len,"Bytes][stack size",var_stack_len,"Bytes]"
	print "======================================================================="

if __name__=='__main__':
	gen_stm32_meminfo()
