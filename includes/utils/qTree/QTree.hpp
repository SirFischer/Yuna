/*
 * File: QTree.hpp
 * Project: Extermination
 * File Created: Sunday, 31st October 2021 7:15:53 am
 * Author: Marek Fischer
 * -----
 * Last Modified: Saturday, 26th February 2022 11:58:08 am
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
	#define MAX_QUADTREE_NODES 9
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
			void	Render(sf::RenderWindow *pWindow, int pLevel);
			void	PointRender(sf::RenderWindow *pWindow, const sf::Vector2f &pPoint);
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

		template <typename T>
		void	QTree<T>::Render(sf::RenderWindow *pWindow, int pLevel)
		{
			if (!pLevel)
				return ;
			sf::VertexArray quad(sf::LineStrip, 4);
			quad[0].position = sf::Vector2f(mRect.left, mRect.top);
			quad[1].position = sf::Vector2f(mRect.left + mRect.width, mRect.top);
			quad[2].position = sf::Vector2f(mRect.left + mRect.width, mRect.top + mRect.height);
			quad[3].position = sf::Vector2f(mRect.left, mRect.top + mRect.height);

			quad[0].color = sf::Color::Red;
			quad[1].color = sf::Color::Red;
			quad[2].color = sf::Color::Red;
			quad[3].color = sf::Color::Red;
			
			pWindow->draw(quad);
			if (mNorthWest)
				mNorthWest->Render(pWindow, pLevel - 1);
			if (mNorthEast)
				mNorthEast->Render(pWindow, pLevel - 1);
			if (mSouthEast)
				mSouthEast->Render(pWindow, pLevel - 1);
			if (mSouthWest)
				mSouthWest->Render(pWindow, pLevel - 1);
		}

		template <typename T>
		void	QTree<T>::PointRender(sf::RenderWindow *pWindow, const sf::Vector2f &pPoint)
		{
			if (!mRect.contains(pPoint))
				return ;

			if (!mNorthEast)
			{
				sf::VertexArray quad(sf::LineStrip, 4);
				quad[0].position = sf::Vector2f(mRect.left, mRect.top);
				quad[1].position = sf::Vector2f(mRect.left + mRect.width, mRect.top);
				quad[2].position = sf::Vector2f(mRect.left + mRect.width, mRect.top + mRect.height);
				quad[3].position = sf::Vector2f(mRect.left, mRect.top + mRect.height);

				quad[0].color = sf::Color::Green;
				quad[1].color = sf::Color::Green;
				quad[2].color = sf::Color::Green;
				quad[3].color = sf::Color::Green;

				pWindow->draw(quad);
			}

			if (mNorthWest)
				mNorthWest->PointRender(pWindow, pPoint);
			if (mNorthEast)
				mNorthEast->PointRender(pWindow, pPoint);
			if (mSouthEast)
				mSouthEast->PointRender(pWindow, pPoint);
			if (mSouthWest)
				mSouthWest->PointRender(pWindow, pPoint);
		}


	} // namespace Utils
} // namespace Yuna
