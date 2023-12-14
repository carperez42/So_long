#variable definition:
PROGRAM =so_long
NAME = solong.a
LIBFT = libft.a
GNL = get_next_line.a
MLX = libmlx.a

#variable definition: paths
DIR_HEADER = header/
DIR_OBJ = obj/
DIR_BIN = bin/
DIR_SRC = src/
DIR_LIBFT_h = libft/$(DIR_HEADER)
DIR_LIBFT_s = libft/$(DIR_SRC)
DIR_LIBFT_a = libft/$(DIR_BIN)
DIR_GNL_h = get_next_line/$(DIR_HEADER)
DIR_GNL_s = get_next_line/$(DIR_SRC)
DIR_GNL_a = get_next_line/$(DIR_BIN)
DIR_MLX = mlx/

#C files
FILES_SRC = 000-main.c 001-error_codes.c 002-verification.c\
			003-verification.c 004-verification.c 005-verification.c\
			006-verification.c 007-verification.c 008-game_load.c\
			009-game_tools.c  010-game_loop.c 011-enemy_motion.c\
			012-enemy_update.c 013-draw_items.c 014-player_motion.c\
			015-player_enemy.c 016-player_wall.c 017-player_reward.c\
			018-player_update.c

#O files 
OBJECTS = $(addprefix $(DIR_OBJ),$(FILES_SRC:.c=.o))

#commands 
COM_COMPILER = gcc
COM_HEADERS = -I $(DIR_HEADER) -I $(DIR_LIBFT_h) -I $(DIR_GNL_h) -I $(DIR_MLX)
COM_FLAGS= -Wall -Werror -Wextra -fsanitize=address -MD $(COM_HEADERS)
COM_MLX_FLAGS = -g -Lmlx -lmlx -framework OpenGL -framework Appkit
COM_STATICLIB = ar rcs
COM_TEMPS = .cache_exists
COM_FOLDERS = mkdir -p
COM_REMOVE = rm -f

#DECLARATED tags
.PHONY: 		all bonus clean fclean re

#CREATION temp subfolders
$(COM_TEMPS):
					@$(COM_FOLDERS) $(DIR_OBJ)
					$(info [SUCCESS] temp folder for $(NAME) created.)

#UPDATE static lib
all:			$(NAME) $(PROGRAM) bonus
$(NAME):		$(OBJECTS)
					@$(COM_FOLDERS) $(DIR_BIN)
					@make -C $(DIR_LIBFT_s) --no-print-directory
					@make -C $(DIR_GNL_s) --no-print-directory					
					@make -C $(DIR_MLX) --no-print-directory
					@cp $(DIR_MLX)$(MLX) $(DIR_BIN)				
					@mv $(DIR_BIN)$(MLX) $(DIR_BIN)$@
					@$(COM_STATICLIB) $(DIR_BIN)$@ $<
					$(info [SUCCESS] static library $(MLX) inserted in $@.)

#COMPILATION
$(DIR_OBJ)%.o:	$(DIR_SRC)%.c | $(COM_TEMPS)
					@$(COM_COMPILER) $(COM_FLAGS) -c $< -o $@
-include $(DIR_OBJ)%.d

#PROGRAM compilation
$(PROGRAM): $(OBJECTS) $(DIR_BIN)$(NAME) $(DIR_LIBFT_a)$(LIBFT) $(DIR_GNL_a)$(GNL)
					@$(COM_COMPILER) $(COM_FLAGS) $(COM_MLX_FLAGS) $^ -o $@
					$(info [SUCCESS] $(PROGRAM) created.)

#BONUS tag
bonus: $(OBJECTS) $(DIR_BIN)$(NAME) $(DIR_LIBFT_a)$(LIBFT) $(DIR_GNL_a)$(GNL)
					@$(COM_COMPILER) $(COM_FLAGS) $(COM_MLX_FLAGS) $^ -o $(PROGRAM)_$@
					$(info [SUCCESS] $(PROGRAM)_$@ created.)

#REMOVE temp files
clean:
					@$(COM_REMOVE) -rf $(DIR_OBJ)
					@$(COM_REMOVE) -f $(COM_TEMPS)
					@make clean -C $(DIR_LIBFT_s) --no-print-directory
					@make clean -C $(DIR_GNL_s) --no-print-directory
					$(info [INFO] temp folders removed.)

#REMOVE compilation
fclean:				clean
					@make fclean -C $(DIR_LIBFT_s) --no-print-directory
					@make fclean -C $(DIR_GNL_s) --no-print-directory
					@make clean -C $(DIR_MLX) --no-print-directory
					@$(COM_REMOVE) -rf $(DIR_BIN)
					@$(COM_REMOVE) -f ./$(PROGRAM)
					@$(COM_REMOVE) -f ./$(PROGRAM)_bonus
					$(info [INFO] static library $(NAME) removed.)
					$(info [INFO] $(PROGRAM) removed.)

#RECREATE static library and process	
re:				fclean all