" add additional include paths
set path+=/media/mercileslie/GOTTAGOFAST/WorkWork/Libraries/vcpkg/installed/x64-linux/include/**2
set path+=/media/mercileslie/GOTTAGOFAST/WorkWork/Libraries/vcpkg/installed/x64-linux/**2

" nnoremap <C-s> :!cd ./scripts && ./format_file.sh %:p<CR>

" save the file and clang format it and redraw the vim editor on pressing zz
nnoremap <silent> zz :update<CR> :silent execute '!cd ./scripts && ./format_file.sh %:p' <CR>:redr!<CR>
" inoremap zz <Esc>:update<CR>gi<CR>:!cd ./scripts && ./format_file.sh %:p<CR>

" nnoremap zz :echo \"hello\" \| echo \"goodbye\"

" Debug build on pressing ,sd
nnoremap <leader>sd :execute '!./scripts/linux_rebuild.sh' <CR>
