/*
 * Chapter 11 - Modules (7/10): Driver
 *
 * Only the umbrella `datamodel` is importable from outside. The partitions
 * are invisible to clients - they're an internal organization detail.
 */
import datamodel;

int main()
{
	DataModel::Address a;
}
