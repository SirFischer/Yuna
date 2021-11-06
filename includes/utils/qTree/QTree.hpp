/*
 * File: QTree.hpp
 * Project: Extermination
 * File Created: Sunday, 31st October 2021 7:15:53 am
 * Author: Marek Fischer
 * -----
 * Last Modified: Sunday, 31st October 2021 11:41:28 am
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2021 Deep Vertic
 */

#pragma once
#include <list>
#include <memory>
#include <SFML/Graphics.hpp>

//This can be overwritten by creating the constant before including this file.
#ifndef MAX_QUADTREE_NODES
	#define MAX_QUADTREE_NODES	4
#endif

namespace Yuna
{
	namespace Utils
	{
		template <typename T>
		struct NodeData
		{
			sf::FloatRect	mRect;
			T				mData;

			NodeData(T pData, sf::FloatRect pRect)
			{
				mRect = pRect;
				mData = pData;
			}
		};

		template <typename T>
		class QTree
		{
		private:
			std::list<NodeData<T>>		mData;
			sf::FloatRect				mRect;

			std::unique_ptr<QTree<T>>	mNorthWest;
			std::unique_ptr<QTree<T>>	mSouthWest;
			std::unique_ptr<QTree<T>>	mSouthEast;
			std::unique_ptr<QTree<T>>	mNorthEast;
			
		public:
			QTree(sf::FloatRect	pRect);
			~QTree();

			bool	Insert(T pData, sf::FloatRect pRect);
			bool	Insert(NodeData<T> pNode);
			void	Subdivide();
			std::list<std::list<NodeData<T>> *> RangeSearch(sf::FloatRect pRect);
			std::list<NodeData<T>> *PointSearch(sf::Vector2f pPoint);
		};

		template <typename T>
		QTree<T>::QTree(sf::FloatRect	pRect)
		{
			mRect = pRect;
		}

		template <typename T>
		QTree<T>::~QTree()
		{
		}

		template <typename T>
		bool		QTree<T>::Insert(T pData, sf::FloatRect pRect)
		{
			NodeData<T> node(pData, pRect);
			return (Insert(node));
		}

		template <typename T>
		bool		QTree<T>::Insert(NodeData<T> pNode)
		{
			if (!pNode.mRect.intersects(mRect))
				return (false);
			if (mData.size() < MAX_QUADTREE_NODES && !mNorthWest)
			{
				mData.push_back(pNode);
				return (true);
			}
			if (!mNorthWest)
				Subdivide();

			if (mNorthWest->Insert(pNode)) return (true);
			if (mNorthEast->Insert(pNode)) return (true);
			if (mSouthEast->Insert(pNode)) return (true);
			if (mSouthWest->Insert(pNode)) return (true);

			return (false);
		}

		template <typename T>
		void		QTree<T>::Subdivide()
		{
			mNorthEast = std::make_unique<QTree<T>>(sf::FloatRect(mRect.left + (mRect.width / 2.f), mRect.top, mRect.width / 2.f, mRect.height / 2.f));
			mNorthWest = std::make_unique<QTree<T>>(sf::FloatRect(mRect.left, mRect.top, mRect.width / 2.f, mRect.height / 2.f));
			mSouthWest = std::make_unique<QTree<T>>(sf::FloatRect(mRect.left, mRect.top + (mRect.height / 2.f), mRect.width / 2.f, mRect.height / 2.f));
			mSouthEast = std::make_unique<QTree<T>>(sf::FloatRect(mRect.left + (mRect.width / 2.f), mRect.top + (mRect.height / 2.f), mRect.width / 2.f, mRect.height / 2.f));
			for (auto &i : mData)
				Insert(i);
			mData.clear();
		}
		
		template <typename T>
		std::list<std::list<NodeData<T>>*> QTree<T>::RangeSearch(sf::FloatRect pRect)
		{
			std::list<std::list<NodeData<T>>*>	list;
			if (!mRect.intersects(pRect))
				return (list);
			list.push_front(&mData);
			if (mNorthWest)
			{
				list.merge(mNorthWest->RangeSearch(pRect));
				list.merge(mNorthEast->RangeSearch(pRect));
				list.merge(mSouthWest->RangeSearch(pRect));
				list.merge(mSouthEast->RangeSearch(pRect));
			}
			return (list);
		}

		template <typename T>
		std::list<NodeData<T>> *QTree<T>::PointSearch(sf::Vector2f pPoint)
		{
			std::list<NodeData<T>>	*res = NULL;
			if (!mRect.contains(pPoint))
				return (NULL);
			if (!mNorthWest)
				return (&mData);
			if ((res = mNorthWest->PointSearch(pPoint))) return (res);
			if ((res = mNorthEast->PointSearch(pPoint))) return (res);
			if ((res = mSouthWest->PointSearch(pPoint))) return (res);
			if ((res = mSouthEast->PointSearch(pPoint))) return (res);
			return (NULL);
		}
	} // namespace Utils
} // namespace Yuna
