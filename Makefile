# Nom du compilateur
CC = gcc

# Répertoire de base pour les dépendances
LIB_DIR = ..

# Liste des dépendances (peut être vide, un ou plusieurs)
DEPENDENCIES = 
# URLs des dépendances (à définir sous forme DEP_URL = <URL>)

# Options de compilation avec les répertoires include des dépendances
CFLAGS = -I include $(foreach dep, $(DEPENDENCIES), -I $(LIB_DIR)/$(dep)/include) -Wall -Wextra -Werror

# Inclusion explicite des fichiers d'en-tête (.h) des dépendances
INCLUDES = $(foreach dep, $(DEPENDENCIES), $(wildcard $(LIB_DIR)/$(dep)/include/*.h))
INCLUDE_FLAGS = $(foreach header, $(INCLUDES), -include $(header))

# Répertoires
SRC_DIR = src
OBJ_DIR = obj
INCLUDE_DIR = include

# Nom de la bibliothèque
LIB = get_next_line.a

# Liste des fichiers sources (.c) dans src et ses sous-répertoires
SRCS = $(shell find $(SRC_DIR) -type f -name "*.c")

# Transformation des fichiers sources en fichiers objets correspondants dans obj
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

# Cible par défaut
all: $(LIB)

# Gestion conditionnelle des dépendances
ifneq ($(strip $(DEPENDENCIES)),)
all: dependencies
endif

# Règle pour gérer les dépendances
dependencies:
	@echo "Vérification des dépendances pour convert..."
	@$(foreach dep, $(DEPENDENCIES), \
		echo "Traitement de la dépendance $(dep)..."; \
		if [ ! -d $(LIB_DIR)/$(dep) ]; then \
			echo "Dépendance $(dep) non trouvée. Clonage depuis $($(dep)_URL)..."; \
			git clone $($(dep)_URL) $(LIB_DIR)/$(dep) || { echo "Échec du clonage de $($(dep)_URL)"; exit 1; }; \
		else \
			echo "Dépendance $(dep) trouvée. Mise à jour en cours..."; \
			cd $(LIB_DIR)/$(dep) && git pull || { echo "Échec de la mise à jour de $(dep)"; exit 1; }; \
		fi; \
		if [ ! -d $(LIB_DIR)/$(dep)/include ]; then \
			echo "Erreur : répertoire include non trouvé dans $(dep)"; \
			exit 1; \
		fi; \
		if [ ! -f $(LIB_DIR)/$(dep)/$(dep).a ]; then \
			echo "Fichier $(dep).a non trouvé. Tentative de compilation..."; \
			cd $(LIB_DIR)/$(dep) && make || { echo "Erreur : impossible de compiler $(dep)"; exit 1; }; \
		fi; \
	)
	@echo "Toutes les dépendances sont satisfaites."

# Règle pour créer la bibliothèque statique
$(LIB): $(OBJS)
	@echo "Création de la bibliothèque $@"
	ar rcs $@ $^

# Règle pour compiler les fichiers objets
# Inclut les fichiers d'en-tête avec -include pour chaque dépendance
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDE_FLAGS) -c $< -o $@

# Nettoyage des fichiers objets
clean:
	@echo "Suppression des fichiers objets..."
	find $(OBJ_DIR) -type f -name "*.o" -delete

# Nettoyage complet (objets + bibliothèque)
fclean: clean
	@echo "Suppression de la bibliothèque $(LIB)"
	rm -f $(LIB)

# Recompilation complète
re: fclean all

# Indique que ces cibles ne sont pas des fichiers
.PHONY: all dependencies clean fclean re
