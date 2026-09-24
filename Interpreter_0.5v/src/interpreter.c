#include "../data/interpreter.h"
#include "../data/parser_datas/AST_node.h"
#include "../data/utils/variables_map.h"
#include "../data/utils/functions_map.h"

static const char *ASTTypeName(ASTNodeType type)
{
	switch (type) {
		case AST_VARIABLE:
			return "VARIABLE";
		case AST_FUNCTION:
			return "FUNCTION";
		case AST_BINARY:
			return "BINARY";
		case AST_CALL:
			return "CALL";
		case AST_LITERAL:
			return "LITERAL";
		default:
			return "UNKNOWN";
	}
}

static void PrintASTBeingInterpreted(ASTNode *node, int index)
{
	printf("\n[Interpreter] AST #%d: %s\n", index, ASTTypeName(node->type));

	switch (node->type) {
		case AST_VARIABLE:
			printf("  identifier: %s\n", node->variable.identifier);
			printf("  type: %s\n", TokenTypeName(node->variable.varType));

			if (node->variable.varType == TYPE_TEXT) {
				printf("  value: %s\n", node->variable.value.text);
			} else {
				printf("  value: %d\n", node->variable.value.intValue);
			}
			break;

		case AST_FUNCTION:
			printf("  name: %s\n", node->function.name);
			break;

		case AST_CALL:
			printf("  name: %s\n", node->call.name);
			break;

		case AST_BINARY:
			printf("  operator: %s\n", TokenTypeName(node->binary.operator));
			break;

		case AST_LITERAL:
			printf("  type: %s\n", TokenTypeName(node->literal.type));
			break;

		default:
			break;
	}
}

void Interpreter(ASTList *headList){
	ASTList *current = headList;
	VariablesMap *variablesMap = VariablesMapInit();
	
	int index = 0;

	printf("\n========== INTERPRETER ==========");

	while (current != NULL) {
		if (current->current != NULL) {
			PrintASTBeingInterpreted(current->current, index);
			CheckAST(current->current, variablesMap);
			index++;
		}

		current = current->next;
	}

	if (index == 0) {
		printf("\nNenhuma AST para interpretar.\n");
	}

	printf("\n=================================\n");
}

int CheckAST(ASTNode *current, VariablesMap *variablesMap){
	if(current->type == AST_VARIABLE){
		VariablesMapAdd(variablesMap, current);
	}
	else if(current->type == AST_CALL){
		RuneFunction functionInLanguage = FunctionsMapGet(current->call.name);

		if(functionInLanguage != NULL){
			functionInLanguage(current, variablesMap);
		}
	}

	return 1;
}
